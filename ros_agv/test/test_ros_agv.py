"""Check the standalone ROS driver using a fake Arduino serial port."""
import struct
import time

import pytest

rclpy = pytest.importorskip('rclpy')
from geometry_msgs.msg import Twist
from ros_agv import ros_agv as driver_module


class FakeSerial:
    def __init__(self):
        self.data = bytearray()
        self.sent = []
        self.closed = False

    @property
    def in_waiting(self):
        return len(self.data)

    def read(self, size):
        data = bytes(self.data[:size])
        del self.data[:size]
        return data

    def write(self, data):
        self.sent.append(data)

    def reset_input_buffer(self):
        self.data.clear()

    def close(self):
        self.closed = True


def feedback(left, right):
    body = bytes([3]) + struct.pack('>II', left, right)
    return bytes([245, 10]) + body + bytes([sum(body) & 255])


@pytest.fixture
def driver(monkeypatch):
    port = FakeSerial()
    monkeypatch.setattr(driver_module.serial, 'Serial', lambda *a, **kw: port)
    monkeypatch.setattr(driver_module.time, 'sleep', lambda seconds: None)
    rclpy.init(args=[])
    node = driver_module.ROSAGVDriver()
    try:
        yield node, port
    finally:
        node.jdamr.close()
        node.destroy_node()
        rclpy.shutdown()


def test_motor_packet_and_close(driver):
    node, port = driver
    node.jdamr.set_motor(-20, 20)
    assert port.sent[-1] == bytes([245, 4, 1, 236, 20, 1])
    node.jdamr.close()
    assert port.sent[-1] == bytes([245, 4, 1, 0, 0, 1])
    assert port.closed


def test_unsigned_partial_and_bad_feedback(driver):
    node, port = driver
    frame = feedback(0x80000001, 123)
    port.data.extend(frame[:5])
    assert node.jdamr.read_encoder() is None
    port.data.extend(frame[5:])
    assert node.jdamr.read_encoder() == (2147483649, 123)
    port.data.extend(frame[:-1] + bytes([frame[-1] ^ 1]))
    assert node.jdamr.read_encoder() is None


def test_drive_and_timeouts(driver):
    node, port = driver
    msg = Twist()
    msg.linear.x = 0.25
    node.cmd_vel_callback(msg)
    port.data.extend(feedback(0, 0))
    node.update()
    assert port.sent[-1] == bytes([245, 4, 1, 50, 50, 101])
    node.last_command = time.monotonic() - 1
    node.update()
    assert port.sent[-1] == bytes([245, 4, 1, 0, 0, 1])
    node.cmd_vel_callback(msg)
    node.last_encoder = time.monotonic() - 1
    node.update()
    assert port.sent[-1] == bytes([245, 4, 1, 0, 0, 1])


def test_reverse_and_invalid_command(driver):
    node, port = driver
    msg = Twist()
    msg.linear.x = -0.25
    node.cmd_vel_callback(msg)
    assert (node.left_speed, node.right_speed) == (-50, -50)
    msg.linear.x = 0.0
    msg.angular.z = 1.0
    node.cmd_vel_callback(msg)
    assert (node.left_speed, node.right_speed) == (-40, 40)
    msg.linear.x = float('nan')
    node.cmd_vel_callback(msg)
    assert (node.left_speed, node.right_speed) == (0, 0)


def test_joint_counts_and_rollover(driver):
    node, port = driver
    node.publish_joint_states(0xFFFFFFFF, 100)
    assert (node.left_position, node.right_position) == (0.0, 0.0)
    node.publish_joint_states(0, 110)
    one_tick = 2 * driver_module.math.pi / driver_module.TICKS_PER_REVOLUTION
    assert node.left_position == pytest.approx(one_tick)
    assert node.right_position == pytest.approx(10 * one_tick)


def test_feedback_recovers_from_noise_and_truncated_packet(driver):
    node, port = driver
    frame = feedback(245, 300)
    port.data.extend(b'noise\xf5\xff\x03' + frame[:7])
    assert node.jdamr.read_encoder() is None
    port.data.extend(feedback(10, 20) + feedback(30, 40))
    assert node.jdamr.read_encoder() == (30, 40)
    assert node.jdamr.read_encoder() is None


def test_cmd_vel_to_feedback_to_joint_states(driver):
    node, port = driver
    received = []
    from sensor_msgs.msg import JointState
    subscription = node.create_subscription(
        JointState, 'joint_states', lambda msg: received.append(msg), 10)
    try:
        counts = [0, 0]
        port.data.extend(feedback(*counts))
        node.update()
        for linear, angular, signs in [
                (0.1, 0.0, (1, 1)), (-0.1, 0.0, (-1, -1)),
                (0.0, 0.5, (-1, 1)), (0.0, -0.5, (1, -1))]:
            msg = Twist()
            msg.linear.x, msg.angular.z = linear, angular
            before = (node.left_position, node.right_position)
            for _ in range(4):
                node.cmd_vel_callback(msg)
                counts = [(value + sign * 10) & 0xFFFFFFFF
                          for value, sign in zip(counts, signs)]
                port.data.extend(feedback(*counts))
                node.update()
                assert port.sent[-1][3:5] == bytes([
                    node.left_speed & 255, node.right_speed & 255])
                rclpy.spin_once(node, timeout_sec=0.01)
            for after, start, sign in zip(
                    (node.left_position, node.right_position), before, signs):
                assert (after - start) * sign > 0
        assert received
        assert received[-1].name == ['left_wheel_joint', 'right_wheel_joint']
        assert len(received[-1].position) == 2
    finally:
        node.destroy_subscription(subscription)
