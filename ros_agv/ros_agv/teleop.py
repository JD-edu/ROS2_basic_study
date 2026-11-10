#!/usr/bin/env python3
"""터미널의 WASD 입력을 cmd_vel로 발행합니다."""

import math
import select
import sys
import termios
import time
import tty

from geometry_msgs.msg import Twist
import rclpy
from rclpy.node import Node


class AGVTeleop(Node):
    """키 입력이 끊기면 정지하는 키보드 조종 노드."""

    def __init__(self):
        super().__init__('ros_agv_teleop')
        self.declare_parameter('linear_speed', 0.1)
        self.declare_parameter('angular_speed', 0.5)
        self.declare_parameter('key_timeout', 0.6)
        self.linear_speed = self.get_parameter('linear_speed').value
        self.angular_speed = self.get_parameter('angular_speed').value
        self.key_timeout = self.get_parameter('key_timeout').value
        for value in (self.linear_speed, self.angular_speed, self.key_timeout):
            if not math.isfinite(value) or value <= 0:
                self.destroy_node()
                raise ValueError('속도와 key_timeout은 유한한 양수여야 합니다.')
        self.publisher = self.create_publisher(Twist, 'cmd_vel', 1)
        self.command = (0.0, 0.0)
        self.last_key = -math.inf

    def handle_key(self, key):
        """방향 키를 속도로 바꾸고 다른 키는 정지로 처리합니다."""
        self.command = {
            'w': (self.linear_speed, 0.0),
            's': (-self.linear_speed, 0.0),
            'a': (0.0, self.angular_speed),
            'd': (0.0, -self.angular_speed),
        }.get(key.lower(), (0.0, 0.0))
        self.last_key = time.monotonic()

    def publish_command(self, stop=False):
        """유효한 명령 또는 정지를 발행합니다."""
        msg = Twist()
        if not stop and time.monotonic() - self.last_key < self.key_timeout:
            msg.linear.x, msg.angular.z = self.command
        self.publisher.publish(msg)


def main(args=None):
    """터미널 설정을 복원하고 종료 시 정지를 요청합니다."""
    if not sys.stdin.isatty():
        print('teleop은 키보드 입력이 가능한 터미널에서 실행하세요.', file=sys.stderr)
        return
    settings = termios.tcgetattr(sys.stdin)
    rclpy.init(args=args)
    node = None
    try:
        node = AGVTeleop()
        print('W: 전진 / S: 후진 / A: 좌회전 / D: 우회전')
        print('Space 또는 다른 키: 정지 / Q 또는 Ctrl+C: 종료')
        print('이동 키를 누르고 계세요. 입력이 끊기면 자동 정지합니다.')
        tty.setcbreak(sys.stdin.fileno())
        while rclpy.ok():
            rclpy.spin_once(node, timeout_sec=0.0)
            if select.select([sys.stdin], [], [], 0.05)[0]:
                key = sys.stdin.read(1)
                if not key or key.lower() == 'q' or key == '\x03':
                    break
                node.handle_key(key)
            node.publish_command()
    except KeyboardInterrupt:
        pass
    finally:
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
        try:
            if node is not None:
                try:
                    if rclpy.ok():
                        node.publish_command(stop=True)
                finally:
                    node.destroy_node()
        finally:
            if rclpy.ok():
                rclpy.shutdown()


if __name__ == '__main__':
    main()
