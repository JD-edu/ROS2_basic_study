#!/usr/bin/env python3

"""
MIT License

Copyright (c) 2024 JD edu
http://jdedu.kr
Author: conner.jeong@gmail.com
"""

import math
import struct
import threading

import rclpy
import serial

from geometry_msgs.msg import Twist
from sensor_msgs.msg import JointState
from rclpy.node import Node


# ---------------------------------------------------------
# 로봇 설정
# ---------------------------------------------------------
SERIAL_PORT = "/dev/ttyUSB0"
BAUDRATE = 115200

WHEEL_SEPARATION = 0.40          # 좌우 바퀴 사이 거리(m)
MAX_LINEAR_SPEED = 0.5           # 모터 명령 100에 해당하는 속도(m/s)
ENCODER_TICKS_PER_REVOLUTION = 1320


class AGVSerial:
    """AGV 제어보드와 시리얼 통신을 담당한다."""

    HEAD = 0xF5
    CMD_SET_MOTOR = 0x01
    CMD_GET_ENCODER = 0x03

    def __init__(self, port, baudrate):
        self.ser = serial.Serial(
            port,
            baudrate,
            timeout=0.1
        )

        self.left_encoder = 0
        self.right_encoder = 0
        self.running = True

        self.thread = threading.Thread(
            target=self.receive_data,
            daemon=True
        )
        self.thread.start()

        print(f"Serial opened: {port}")

    def receive_data(self):
        """제어보드에서 엔코더 패킷을 계속 읽는다."""

        while self.running:

            # 헤더 1바이트 읽기
            head = self.ser.read(1)

            if not head:
                continue

            if head[0] != self.HEAD:
                continue

            # 패킷 길이 읽기
            length_data = self.ser.read(1)

            if not length_data:
                continue

            length = length_data[0]

            # command + payload + checksum 읽기
            packet = self.ser.read(length)

            if len(packet) != length:
                continue

            command = packet[0]
            payload = packet[1:-1]

            if command == self.CMD_GET_ENCODER:
                self.parse_encoder(payload)

    def parse_encoder(self, payload):
        """왼쪽과 오른쪽 엔코더 값을 읽는다."""

        if len(payload) < 8:
            return

        self.left_encoder = int.from_bytes(
            payload[0:4],
            byteorder="big",
            signed=True
        )

        self.right_encoder = int.from_bytes(
            payload[4:8],
            byteorder="big",
            signed=True
        )

    def set_motor(self, left_speed, right_speed):
        """좌우 모터에 -100~100 범위의 속도를 전송한다."""

        left_speed = max(-100, min(100, int(left_speed)))
        right_speed = max(-100, min(100, int(right_speed)))

        motor_data = struct.pack(
            "bb",
            left_speed,
            right_speed
        )

        # length = command 1 + motor data 2 + checksum 1
        length = 4
        checksum = 0xFF

        packet = bytes([
            self.HEAD,
            length,
            self.CMD_SET_MOTOR
        ]) + motor_data + bytes([checksum])

        self.ser.write(packet)

    def close(self):
        """모터를 정지하고 시리얼 포트를 닫는다."""

        self.set_motor(0, 0)
        self.running = False

        if self.ser.is_open:
            self.ser.close()


class ROSAGVDriver(Node):
    """cmd_vel을 받아 AGV를 제어하고 바퀴 상태를 발행한다."""

    def __init__(self):
        super().__init__("ros_agv_driver")

        self.agv = AGVSerial(
            SERIAL_PORT,
            BAUDRATE
        )

        # cmd_vel 구독
        self.create_subscription(
            Twist,
            "/cmd_vel",
            self.cmd_vel_callback,
            10
        )

        # joint_states 발행
        self.joint_pub = self.create_publisher(
            JointState,
            "/joint_states",
            10
        )

        # 20Hz로 JointState 발행
        self.create_timer(
            0.05,
            self.publish_joint_states
        )

        self.get_logger().info("ROS AGV driver started")

    def cmd_vel_callback(self, msg):
        """cmd_vel을 좌우 모터 속도로 변환한다."""

        linear = msg.linear.x
        angular = msg.angular.z

        # 차동구동 로봇의 좌우 바퀴 속도
        left_velocity = (
            linear
            - angular * WHEEL_SEPARATION / 2.0
        )

        right_velocity = (
            linear
            + angular * WHEEL_SEPARATION / 2.0
        )

        # m/s를 -100~100 모터 명령으로 변환
        left_motor = (
            left_velocity
            / MAX_LINEAR_SPEED
            * 100
        )

        right_motor = (
            right_velocity
            / MAX_LINEAR_SPEED
            * 100
        )

        self.agv.set_motor(
            left_motor,
            right_motor
        )

        self.get_logger().info(
            f"left={int(left_motor)}, "
            f"right={int(right_motor)}"
        )

    def publish_joint_states(self):
        """엔코더 값을 바퀴 회전각으로 변환해 발행한다."""

        radians_per_tick = (
            2.0 * math.pi
            / ENCODER_TICKS_PER_REVOLUTION
        )

        left_position = (
            self.agv.left_encoder
            * radians_per_tick
        )

        right_position = (
            self.agv.right_encoder
            * radians_per_tick
        )

        msg = JointState()

        msg.header.stamp = (
            self.get_clock().now().to_msg()
        )

        msg.name = [
            "left_wheel_joint",
            "right_wheel_joint"
        ]

        msg.position = [
            left_position,
            right_position
        ]

        self.joint_pub.publish(msg)

    def stop(self):
        self.agv.close()


def main(args=None):
    rclpy.init(args=args)

    node = ROSAGVDriver()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass

    finally:
        node.stop()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()