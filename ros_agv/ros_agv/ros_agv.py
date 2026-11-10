#!/usr/bin/env python3
"""2륜 로봇 제어와 엔코더 확인을 위한 ROS 2 입문 예제."""
import math
import time

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import JointState
import serial

# -----------------------------------------------------------------------------
# ROS 2 노드 -> 아두이노 모터 제어 프로토콜
# 단독 PC 테스트도 같은 패킷을 사용합니다. 통신: USB Serial, 115200 baud, 8N1.
# ROS의 cmd_vel(Twist)은 Python에서 좌우 속도로 변환하며, 아두이노에는
# Twist 자체가 아닌 아래의 6바이트 이진 패킷을 보냅니다.
#
# 바이트 위치  의미          값
#     0       헤더          0xF5 (패킷 시작)
#     1       길이          0x04 (명령 1 + 좌우 속도 2 + 체크섬 1)
#     2       명령          0x01 (좌우 모터 제어)
#     3       왼쪽 속도     signed int8, -100~100
#     4       오른쪽 속도   signed int8, -100~100
#     5       체크섬        (명령 + 왼쪽 속도 바이트 + 오른쪽 속도 바이트) & 0xFF
#
# 속도는 m/s가 아닌 모터 출력 명령입니다. 양수=전진, 음수=후진, 0=정지.
# 음수는 2의 보수로 전송합니다. 예: -20 & 0xFF = 236 = 0xEC.
# 체크섬 계산에는 헤더와 길이를 포함하지 않습니다.
# 예: 좌우 20, 20 -> F5 04 01 14 14 29 (모두 16진수)
# 예: 좌우 -20, 20 -> F5 04 01 EC 14 01 (모두 16진수)
# 예: 정지 0, 0 -> F5 04 01 00 00 01 (모두 16진수)
# 아두이노는 유효한 모터 명령을 500ms 동안 받지 못하면 자동 정지합니다.
# -----------------------------------------------------------------------------

# 로봇에 맞게 수정할 설정입니다.
SERIAL_PORT = '/dev/ttyUSB0'
WHEEL_SEPARATION = 0.40       # 좌우 바퀴 사이 거리(m)
MAX_WHEEL_SPEED = 0.5        # 모터 명령 100에 해당하는 바퀴 속도(m/s)
TICKS_PER_REVOLUTION = 1320  # 바퀴 한 바퀴의 엔코더 펄스 수
CMD_TIMEOUT = 0.3            # 명령이 끊기면 정지할 시간(s)
ENCODER_TIMEOUT = 0.5        # 엔코더 통신이 끊기면 정지할 시간(s)


class JDamr:
    """아두이노에 모터 명령을 보내고 엔코더를 읽습니다."""

    def __init__(self, port, logger=None):
        self.rx_buffer = bytearray()
        self.logger = logger
        if logger:
            logger.info(f'[시리얼] 연결 시작: {port}, 115200 baud')
        self.ser = serial.Serial(port, 115200, timeout=0.1, write_timeout=0.1, exclusive=True)
        try:
            if logger:
                logger.info('[시리얼] 포트 열림, 아두이노 재시작 대기(2초)')
            time.sleep(2)  # USB 연결 후 아두이노 재시작 대기
            self.ser.reset_input_buffer()
            self.set_motor(0, 0)
            if logger:
                logger.info('[시리얼] 초기 정지 명령 전송 완료')
        except Exception:
            self.ser.close()
            raise

    def set_motor(self, left, right):
        # 속도를 -100~100 범위로 제한합니다.
        left = max(-100, min(100, int(left)))
        right = max(-100, min(100, int(right)))

        # 음수 속도도 한 바이트로 표현합니다.
        left_byte = left & 0xFF
        right_byte = right & 0xFF
        checksum = (0x01 + left_byte + right_byte) & 0xFF
        packet = bytes([0xF5, 4, 0x01, left_byte, right_byte, checksum])
        self.ser.write(packet)

    def read_encoder(self):
        # 조각난 패킷은 보관하고 잡음/손상 뒤에는 한 바이트씩 재동기화합니다.
        waiting = self.ser.in_waiting
        if waiting:
            self.rx_buffer.extend(self.ser.read(waiting))
        latest = None
        while self.rx_buffer:
            if self.rx_buffer[0] != 0xF5:
                del self.rx_buffer[0]
                continue
            if len(self.rx_buffer) < 3:
                break
            if self.rx_buffer[1:3] != b'\x0a\x03':
                del self.rx_buffer[0]
                continue
            if len(self.rx_buffer) < 12:
                break
            packet = self.rx_buffer[:12]
            if (sum(packet[2:11]) & 0xFF) != packet[11]:
                del self.rx_buffer[0]
                continue
            latest = (int.from_bytes(packet[3:7], 'big'),
                      int.from_bytes(packet[7:11], 'big'))
            del self.rx_buffer[:12]
        return latest

    def close(self):
        if self.logger:
            self.logger.info('[종료] 모터 정지 명령 전송 및 시리얼 닫기')
        try:
            self.set_motor(0, 0)
        finally:
            self.ser.close()


class ROSAGVDriver(Node):
    """cmd_vel 구독, 모터 제어, joint_states 발행을 담당합니다."""

    def __init__(self):
        super().__init__('ros_agv_driver')
        self.get_logger().info('[초기화] ros_agv_driver 시작')
        self.declare_parameter('serial_port', SERIAL_PORT)
        port = self.get_parameter('serial_port').value
        try:
            self.jdamr = JDamr(port, self.get_logger())
        except Exception as exc:
            self.get_logger().error(f'[초기화] 시리얼 연결 실패: {exc}')
            self.destroy_node()
            raise

        self.left_speed = 0
        self.right_speed = 0
        self.last_command = time.monotonic() - 1
        self.last_encoder = time.monotonic() - 1
        self.previous_counts = None
        self.left_position = 0.0
        self.right_position = 0.0
        self.control_state = None
        self.last_status_log = time.monotonic()
        self.encoder_counts = None

        self.publisher_ = self.create_publisher(JointState, 'joint_states', 10)
        self.subscription = self.create_subscription(
            Twist, 'cmd_vel', self.cmd_vel_callback, 1)
        self.timer = self.create_timer(0.02, self.update)
        self.get_logger().info(
            f'[준비 완료] 구독={self.subscription.topic_name}, '
            f'발행={self.publisher_.topic_name}, 제어 주기=0.02초, '
            f'명령 타임아웃={CMD_TIMEOUT}초, 엔코더 타임아웃={ENCODER_TIMEOUT}초')

    def cmd_vel_callback(self, msg):
        linear = msg.linear.x
        angular = msg.angular.z
        if not math.isfinite(linear) or not math.isfinite(angular):
            self.get_logger().warning(
                '[명령] NaN/Inf 속도 수신: 정지 명령으로 처리', throttle_duration_sec=2.0)
            self.left_speed = 0
            self.right_speed = 0
            return

        # 차동구동: 직진 속도와 회전 속도를 좌우 바퀴 속도로 바꿉니다.
        left = linear - angular * WHEEL_SEPARATION / 2
        right = linear + angular * WHEEL_SEPARATION / 2

        # 좌우 속도 비율을 유지하며 -100~100 명령으로 변환합니다.
        maximum = max(MAX_WHEEL_SPEED, abs(left), abs(right))
        self.left_speed = round(left / maximum * 100)
        self.right_speed = round(right / maximum * 100)
        self.last_command = time.monotonic()
        self.get_logger().info(
            f'[명령 수신] linear.x={linear:.3f} m/s, angular.z={angular:.3f} rad/s '
            f'-> 좌/우 모터={self.left_speed}/{self.right_speed}',
            throttle_duration_sec=2.0)

    def publish_joint_states(self, left_count, right_count):
        if self.previous_counts is None:
            self.previous_counts = (left_count, right_count)
            self.get_logger().info(
                f'[엔코더] 첫 정상 패킷 수신: 좌={left_count}, 우={right_count}, 위치 기준=0')

        # 이전 값과의 차이가 이번에 회전한 양입니다.
        # 32비트 모듈러 차이를 signed로 복원하여 후진과 카운터 래핑을 처리합니다.
        left_delta = ((left_count - self.previous_counts[0] + 0x80000000) & 0xFFFFFFFF) - 0x80000000
        right_delta = ((right_count - self.previous_counts[1] + 0x80000000) & 0xFFFFFFFF) - 0x80000000
        self.previous_counts = (left_count, right_count)
        self.left_position += left_delta * 2 * math.pi / TICKS_PER_REVOLUTION
        self.right_position += right_delta * 2 * math.pi / TICKS_PER_REVOLUTION

        msg = JointState()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.name = ['left_wheel_joint', 'right_wheel_joint']
        msg.position = [self.left_position, self.right_position]
        self.publisher_.publish(msg)

    def update(self):
        try:
            self._update()
        except Exception as exc:
            self.get_logger().error(f'[제어 오류] 통신/상태 갱신 실패, 노드 종료: {exc}')
            raise

    def _update(self):
        # 1. 엔코더를 읽고 바퀴 회전량을 발행합니다.
        counts = self.jdamr.read_encoder()
        if counts is not None:
            left, right = counts
            self.publish_joint_states(left, right)
            self.last_encoder = time.monotonic()
            self.encoder_counts = counts

        # 2. 명령이나 엔코더 통신이 끊기면 정지합니다.
        now = time.monotonic()
        if now - self.last_command > CMD_TIMEOUT:
            state = '명령 대기/타임아웃: 모터 정지'
            motor = (0, 0)
        elif now - self.last_encoder > ENCODER_TIMEOUT:
            state = '엔코더 대기/타임아웃: 모터 정지'
            motor = (0, 0)
        else:
            state = '정상 제어'
            motor = (self.left_speed, self.right_speed)
        self.jdamr.set_motor(*motor)
        if state != self.control_state:
            message = f'[제어 상태] {state}, 전송 좌/우={motor[0]}/{motor[1]}'
            if state == '정상 제어':
                self.get_logger().info(message)
            else:
                self.get_logger().warning(message)
            self.control_state = state
        if now - self.last_status_log >= 2.0:
            command_age = now - self.last_command
            encoder_age = now - self.last_encoder
            self.get_logger().info(
                f'[상태] {state}, 전송 좌/우={motor[0]}/{motor[1]}, '
                f'명령 경과={command_age:.2f}초, 엔코더 경과={encoder_age:.2f}초, '
                f'엔코더 누적={self.encoder_counts}, '
                f'joint 위치={self.left_position:.3f}/{self.right_position:.3f} rad')
            self.last_status_log = now


def main(args=None):
    rclpy.init(args=args)
    driver = None
    try:
        driver = ROSAGVDriver()
        rclpy.spin(driver)
    except KeyboardInterrupt:
        if driver is not None:
            driver.get_logger().info('[종료] Ctrl+C 수신')
    finally:
        try:
            if driver is not None:
                try:
                    driver.jdamr.close()
                finally:
                    driver.destroy_node()
        finally:
            if rclpy.ok():
                rclpy.shutdown()


if __name__ == '__main__':
    main()
