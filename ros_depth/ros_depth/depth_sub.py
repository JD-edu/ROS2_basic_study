"""Receive and display a 16UC1 depth image stream."""

import threading
import time

import cv2
import numpy as np
import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image


class DepthSubscriber(Node):
    """Keep only the newest depth frame to minimize display latency."""

    def __init__(self):
        super().__init__('depth_subscriber')

        self.declare_parameter('depth_topic', '/camera/depth/image_raw')
        self.declare_parameter('max_depth_mm', 5000)
        depth_topic = self.get_parameter('depth_topic').value

        self._lock = threading.Lock()
        self._latest_depth = None
        self._subscription = self.create_subscription(
            Image,
            depth_topic,
            self._image_callback,
            qos_profile_sensor_data,
        )
        self.get_logger().info(
            f'16UC1 depth image waiting on {depth_topic}'
        )

    def _image_callback(self, msg):
        if msg.encoding not in ('16UC1', 'mono16'):
            self.get_logger().warning(
                f'Unsupported encoding: {msg.encoding} (expected 16UC1)',
                throttle_duration_sec=5.0,
            )
            return

        if msg.height == 0 or msg.width == 0 or msg.step < msg.width * 2:
            self.get_logger().warning('Invalid depth image dimensions')
            return

        row_values = msg.step // 2
        required_values = row_values * msg.height
        if len(msg.data) < required_values * 2:
            self.get_logger().warning('Incomplete depth image received')
            return

        depth = np.frombuffer(msg.data, dtype=np.uint16, count=required_values)
        depth = depth.reshape(msg.height, row_values)[:, :msg.width]
        message_is_big_endian = bool(msg.is_bigendian)
        host_is_big_endian = not np.little_endian
        if message_is_big_endian != host_is_big_endian:
            depth = depth.byteswap()

        with self._lock:
            self._latest_depth = depth.copy()

    def latest_depth(self):
        with self._lock:
            return self._latest_depth


def colorize_depth(depth, max_depth_mm):
    """Convert millimetre depth values to an easy-to-read color image."""
    clipped = np.clip(depth, 0, max_depth_mm)
    display = cv2.convertScaleAbs(clipped, alpha=255.0 / max_depth_mm)
    display = cv2.applyColorMap(255 - display, cv2.COLORMAP_TURBO)
    display[depth == 0] = 0

    height, width = depth.shape
    center_depth = int(depth[height // 2, width // 2])
    cv2.drawMarker(
        display,
        (width // 2, height // 2),
        (255, 255, 255),
        cv2.MARKER_CROSS,
        18,
        2,
    )
    label = 'center: invalid' if center_depth == 0 else f'center: {center_depth} mm'
    cv2.putText(
        display,
        label,
        (15, 30),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.7,
        (255, 255, 255),
        2,
        cv2.LINE_AA,
    )
    return display


def main(args=None):
    rclpy.init(args=args)
    node = DepthSubscriber()

    def spin_node():
        try:
            rclpy.spin(node)
        except (KeyboardInterrupt, ExternalShutdownException):
            pass

    executor_thread = threading.Thread(
        target=spin_node,
        daemon=True,
    )
    executor_thread.start()

    try:
        while rclpy.ok():
            depth = node.latest_depth()
            if depth is not None:
                max_depth_mm = max(
                    1,
                    int(node.get_parameter('max_depth_mm').value),
                )
                cv2.imshow(
                    'camera depth (16UC1)',
                    colorize_depth(depth, max_depth_mm),
                )
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
            time.sleep(0.005)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        cv2.destroyAllWindows()
        if rclpy.ok():
            rclpy.shutdown()
        try:
            executor_thread.join(timeout=1.0)
        except KeyboardInterrupt:
            pass


if __name__ == '__main__':
    main()
