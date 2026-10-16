"""Subscribe to ROS 2 camera images and display them with OpenCV."""

import cv2
import rclpy
from cv_bridge import CvBridge
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image


class ImageSubscriber(Node):
    """Display images received from the camera publisher."""

    def __init__(self):
        """Create the image subscription."""
        super().__init__('image_subscriber')
        self.subscription = self.create_subscription(
            Image,
            'video_frames',
            self.listener_callback,
            qos_profile_sensor_data,
        )
        self.bridge = CvBridge()

    def listener_callback(self, data):
        """Convert and display a received image."""
        current_frame = self.bridge.imgmsg_to_cv2(
            data, desired_encoding='bgr8')
        cv2.imshow('camera', current_frame)
        cv2.waitKey(1)


def main(args=None):
    """Run the image subscriber node."""
    rclpy.init(args=args)
    image_subscriber = ImageSubscriber()

    try:
        rclpy.spin(image_subscriber)
    except KeyboardInterrupt:
        pass
    finally:
        image_subscriber.destroy_node()
        cv2.destroyAllWindows()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
