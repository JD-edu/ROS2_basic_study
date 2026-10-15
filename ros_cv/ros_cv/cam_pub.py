

# Basic ROS 2 program to publish real-time streaming 
# video from your built-in webcam
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com
  
# Import the necessary libraries
import rclpy # Python Client Library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import CompressedImage # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
import cv2 # OpenCV library
 
class ImagePublisher(Node):
  """
  Create an ImagePublisher class, which is a subclass of the Node class.
  """
  def __init__(self):
    """
    Class constructor to set up the node
    """
    # Initiate the Node class's constructor and give it a name
    super().__init__('image_publisher')
    self.declare_parameter('camera_device', '/dev/video0')
    camera_device = self.get_parameter('camera_device').value

    # 1. 초저지연 QoS 프로파일 정의 (핵심)
    qos_profile = QoSProfile(
        reliability=ReliabilityPolicy.BEST_EFFORT,  # 재전송 방지
        history=HistoryPolicy.KEEP_LAST,
        depth=1                                     # 버퍼 크기 1
    )
      
    # Create the publisher. This publisher will publish an Image
    # to the video_frames topic. The queue size is 10 messages.
    self.publisher_ = self.create_publisher(CompressedImage, 'video_frames', qos_profile)
      
    # We will publish a message every 0.1 seconds
    timer_period = 0.1  # seconds
      
    # Create the timer
    self.timer = self.create_timer(timer_period, self.timer_callback)
         
    # Create a VideoCapture object
    # A stable /dev/v4l/by-id/... path can also be passed by the launch file.
    self.cap = cv2.VideoCapture(camera_device, cv2.CAP_V4L2)
    if not self.cap.isOpened():
      self.cap.release()
      raise RuntimeError(f"카메라를 열 수 없습니다: {camera_device}")
         
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()
   
  def timer_callback(self):
    """
    Callback function.
    This function gets called every 0.1 seconds.
    """
    # Capture frame-by-frame
    # This method returns True/False as well
    # as the video frame.
    ret, frame = self.cap.read()
          
    if ret == True:
      # Publish the image.
      # The 'cv2_to_imgmsg' method converts an OpenCV
      # image to a ROS 2 image message
      self.publisher_.publish(self.br.cv2_to_compressed_imgmsg(frame))
 
    # Display the message on the console
    self.get_logger().info('Publishing video frame')
  
def main(args=None):
  
    # Initialize the rclpy library
    rclpy.init(args=args)
    
    # Create the node
    image_publisher = ImagePublisher()
    
    # Spin the node so the callback function is called.
    rclpy.spin(image_publisher)
    
    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    image_publisher.destroy_node()
    
    # Shutdown the ROS client library for Python
    rclpy.shutdown()
    
if __name__ == '__main__':
    main()
