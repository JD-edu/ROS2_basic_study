"""Publish Arduino virtual lidar scans as sensor_msgs/LaserScan."""

import math

import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import LaserScan

from diy_lidar.protocol import RANGE_MAX, RANGE_MIN, SAMPLE_COUNT, SerialScans


class LidarBridge(Node):
    """Bridge a nonblocking USB serial stream to ROS2."""

    def __init__(self):
        super().__init__('lidar_bridge')
        port = self.declare_parameter('port', '/dev/ttyACM0').value
        baud = self.declare_parameter('baud', 115200).value
        self.frame_id = self.declare_parameter('frame_id', 'laser_frame').value
        topic = self.declare_parameter('topic', '/scan').value
        self.source = SerialScans(port, baud)
        self.publisher = self.create_publisher(LaserScan, topic, qos_profile_sensor_data)
        self.timer = self.create_timer(0.01, self.publish_scan)
        self.get_logger().info(f'{port} ({baud} baud) -> {topic}')

    def publish_scan(self):
        """Publish the latest complete scan; stop cleanly on disconnection."""
        try:
            scan = self.source.poll()
        except OSError as exc:
            self.get_logger().error(f'Serial disconnected: {exc}; restart the bridge')
            self.timer.cancel()
            self.source.close()
            return
        if scan is None:
            return
        period, ranges = scan
        msg = LaserScan()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = self.frame_id
        msg.angle_min = 0.0
        msg.angle_increment = math.tau / SAMPLE_COUNT
        msg.angle_max = (SAMPLE_COUNT - 1) * msg.angle_increment
        msg.scan_time = period
        # The simulated rays form one instantaneous snapshot.
        msg.time_increment = 0.0
        msg.range_min = RANGE_MIN
        msg.range_max = RANGE_MAX
        msg.ranges = ranges
        self.publisher.publish(msg)


def main(args=None):
    """Run the serial bridge."""
    rclpy.init(args=args)
    node = None
    try:
        node = LidarBridge()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if node is not None:
            node.source.close()
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
