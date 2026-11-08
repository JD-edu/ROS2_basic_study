#!/usr/bin/env python3
"""Two-wheel differential drive with encoder feedback and command watchdog."""
import math
import struct
import time

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import JointState
import serial

from ros_agv.protocol import CMD_ENCODER, Decoder, encoder_delta, motor_packet
from ros_agv.protocol import wheel_commands


class ROSAGVDriver(Node):
    """Control left/right motors through the matching Arduino firmware."""

    def __init__(self):
        super().__init__('ros_agv_driver')
        defaults = {
            'serial_port': '/dev/ttyUSB0', 'baudrate': 115200,
            'wheel_separation': 0.40, 'max_wheel_speed': 0.5,
            'encoder_ticks_per_revolution': 1320.0,
            'cmd_vel_timeout': 0.3, 'encoder_timeout': 0.5,
            'startup_delay': 2.0,
            'left_joint_name': 'left_wheel_joint',
            'right_joint_name': 'right_wheel_joint',
        }
        for name, value in defaults.items():
            self.declare_parameter(name, value)
        for name in ('wheel_separation', 'max_wheel_speed',
                     'encoder_ticks_per_revolution', 'cmd_vel_timeout',
                     'encoder_timeout'):
            value = self.value(name)
            if not math.isfinite(value) or value <= 0:
                raise ValueError(f'{name} must be finite and positive')
        if self.value('cmd_vel_timeout') >= 0.5:
            raise ValueError('cmd_vel_timeout must be below firmware watchdog (0.5 s)')
        delay = self.value('startup_delay')
        if not math.isfinite(delay) or delay < 0:
            raise ValueError('startup_delay must be finite and nonnegative')
        self.ser = serial.Serial(self.value('serial_port'), self.value('baudrate'),
                                 timeout=0, write_timeout=0.1)
        try:
            time.sleep(delay)
            self.ser.reset_input_buffer()
            self.ser.write(motor_packet(0, 0))
        except Exception:
            self.ser.close()
            raise
        self.decoder = Decoder()
        self.target = (0, 0)
        self.last_command = float('-inf')
        self.last_encoder = float('-inf')
        self.previous_ticks = None
        self.positions = [0.0, 0.0]
        self.failed = False
        self.joint_pub = self.create_publisher(JointState, 'joint_states', 10)
        self.subscription = self.create_subscription(
            Twist, 'cmd_vel', self.cmd_vel_callback, 1)
        self.timer = self.create_timer(0.02, self.update)
        self.get_logger().info('AGV ready; waiting for encoder feedback')

    def value(self, name):
        """Read a startup parameter."""
        return self.get_parameter(name).value

    def cmd_vel_callback(self, msg):
        """Convert m/s and rad/s to proportionally limited motor commands."""
        if self.failed:
            return
        if not all(math.isfinite(v) for v in (msg.linear.x, msg.angular.z)):
            self.target = (0, 0)
            self.last_command = float('-inf')
            self.get_logger().error('Rejected non-finite cmd_vel')
            return
        self.target = wheel_commands(msg.linear.x, msg.angular.z,
                                     self.value('wheel_separation'),
                                     self.value('max_wheel_speed'))
        self.last_command = time.monotonic()

    def update(self):
        """Receive feedback and refresh the firmware watchdog without threads."""
        if self.failed:
            return
        now = time.monotonic()
        try:
            for command, payload in self.decoder.feed(self.ser.read(4096)):
                if command != CMD_ENCODER or len(payload) != 8:
                    continue
                ticks = struct.unpack('>ii', payload)
                if self.previous_ticks is None:
                    self.previous_ticks = ticks
                scale = 2 * math.pi / self.value('encoder_ticks_per_revolution')
                for i in range(2):
                    self.positions[i] += encoder_delta(
                        ticks[i], self.previous_ticks[i]) * scale
                self.previous_ticks = ticks
                self.last_encoder = now
                msg = JointState()
                msg.header.stamp = self.get_clock().now().to_msg()
                msg.name = [self.value('left_joint_name'), self.value('right_joint_name')]
                msg.position = list(self.positions)
                self.joint_pub.publish(msg)
            fresh = (now - self.last_command < self.value('cmd_vel_timeout') and
                     now - self.last_encoder < self.value('encoder_timeout'))
            self.ser.write(motor_packet(*(self.target if fresh else (0, 0))))
        except (serial.SerialException, OSError) as exc:
            self.failed = True
            self.target = (0, 0)
            self.get_logger().error(
                f'Serial failure: {exc}; firmware watchdog stops motors. Restart node.')
            try:
                self.ser.write(motor_packet(0, 0))
            except (serial.SerialException, OSError):
                pass

    def stop(self):
        """Stop and close, including on interruption."""
        self.timer.cancel()
        try:
            if self.ser.is_open:
                self.ser.write(motor_packet(0, 0))
        except (serial.SerialException, OSError) as exc:
            self.get_logger().error(f'Could not send final stop: {exc}')
        finally:
            self.ser.close()


def main(args=None):
    """Run the driver."""
    rclpy.init(args=args)
    node = None
    try:
        node = ROSAGVDriver()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if node is not None:
            node.stop()
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
