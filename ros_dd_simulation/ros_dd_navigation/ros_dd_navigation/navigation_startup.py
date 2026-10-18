"""Start Nav2 only after localization supplies a current map-to-robot transform."""
import time

from nav2_msgs.srv import ManageLifecycleNodes
import rclpy
from rclpy.clock import Clock, ClockType
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node
from rclpy.time import Time
from tf2_ros import Buffer, TransformException, TransformListener


class NavigationStartup(Node):
    """Wait without a user-input timeout, then ask the manager to start Nav2."""

    def __init__(self):
        super().__init__('navigation_startup')
        self.declare_parameter('global_frame', 'map')
        self.declare_parameter('robot_base_frame', 'base_link')
        self.buffer = Buffer(node=self)
        self.listener = TransformListener(self.buffer, self)
        self.client = self.create_client(
            ManageLifecycleNodes, 'lifecycle_manager_navigation/manage_nodes')
        self.future = None
        self.done = False
        self.success = False
        self.last_notice = 0.0
        self.timer = self.create_timer(
            0.25, self.check, clock=Clock(clock_type=ClockType.STEADY_TIME))

    def localized(self):
        try:
            transform = self.buffer.lookup_transform(
                self.get_parameter('global_frame').value,
                self.get_parameter('robot_base_frame').value, Time())
            now = self.get_clock().now()
            stamp = Time.from_msg(transform.header.stamp, clock_type=now.clock_type)
            return now.nanoseconds > 0 and abs((now - stamp).nanoseconds) < 3_000_000_000
        except TransformException:
            return False

    def check(self):
        if self.future is not None:
            if self.future.done():
                try:
                    self.success = bool(self.future.result().success)
                    if self.success:
                        self.get_logger().info('Nav2 ready: navigation goals can now be sent.')
                    else:
                        self.get_logger().error('Nav2 startup failed; inspect lifecycle manager logs.')
                except Exception as error:
                    self.get_logger().error(f'Nav2 startup service failed: {error}')
                self.done = True
                self.timer.cancel()
            return
        if not self.localized():
            now = time.monotonic()
            if now - self.last_notice >= 5.0:
                self.get_logger().info(
                    'Waiting for AMCL localization. Set 2D Pose Estimate in RViz; '
                    'Nav2 activation will start afterwards.')
                self.last_notice = now
            return
        if self.client.service_is_ready():
            request = ManageLifecycleNodes.Request()
            request.command = ManageLifecycleNodes.Request.STARTUP
            self.get_logger().info('Localization ready; starting Nav2 lifecycle nodes.')
            self.future = self.client.call_async(request)


def main(args=None):
    rclpy.init(args=args)
    node = NavigationStartup()
    try:
        while rclpy.ok() and not node.done:
            rclpy.spin_once(node, timeout_sec=0.25)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
    if node.done and not node.success:
        raise SystemExit(1)
