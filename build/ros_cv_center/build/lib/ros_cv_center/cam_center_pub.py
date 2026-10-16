'''
/*MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.*/
'''

# Basic ROS 2 program to publish real-time streaming 
# video from your built-in webcam
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com
  
# Import the necessary libraries
import rclpy # Python Client Library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
import numpy as np
from cv_msg.msg import MsgCenter
 
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
      
    # Create the publisher. This publisher will publish an Image
    # to the video_frames topic. The queue size is 10 messages.
    self.publisher_img = self.create_publisher(Image, 'video_frames', 10)
    self.publisher_xy = self.create_publisher(MsgCenter, 'red_center', 10)
      
    # We will publish a message every 0.1 seconds
    timer_period = 0.1  # seconds
      
    # Create the timer
    self.timer = self.create_timer(timer_period, self.timer_callback)
         
    # Create a VideoCapture object
    # The argument '0' gets the default webcam.
    self.cap = cv2.VideoCapture(0)
         
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()

    self.cx = 0
    self.cy = 0
   
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
      frame, self.cx, self.cy  = self.find_and_mark_red_object(frame)
      cv2.imshow('red', frame)
      cv2.waitKey(1)
      # Publish the image.
      # The 'cv2_to_imgmsg' method converts an OpenCV
      # image to a ROS 2 image message
      self.publisher_img.publish(self.br.cv2_to_imgmsg(frame))
      msg = MsgCenter()
      msg.x = self.cx
      msg.y = self.cy
      self.publisher_xy.publish(msg)
 
      # Display the message on the console
      self.get_logger().info('Publishing video frame')
      print(self.cx, self.cy)

  def find_and_mark_red_object(self, img):
    """
    Finds the red object in an image and draws a red dot at its center.

    Args:
        img: A NumPy array representing the image.

    Returns:
        The image with a red dot at the center of the red object.
    """

    cx = 0
    cy = 0

    # Convert image to HSV color space for better color detection
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # Define lower and upper bounds for red color in HSV
    lower_red = np.array([0, 120, 70])
    upper_red = np.array([10, 255, 255])

    # Create a mask for red color
    mask = cv2.inRange(hsv, lower_red, upper_red)

    # Find contours in the   
    contours, mask = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if len(contours) > 0:
      # Find the largest contour   
      #(assuming it's the red object)
      largest_contour = max(contours, key=cv2.contourArea)

      # Find the center of the largest contour
      M = cv2.moments(largest_contour)
      if M["m00"] != 0:
          cx = int(M["m10"] / M["m00"])
          cy = int(M["m01"] / M["m00"])

          # Draw a red dot at the center
          cv2.circle(img, (cx, cy), 5, (0, 0, 255), -1)

    return img, cx, cy
  
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
