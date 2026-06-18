import rclpy
import serial
from rclpy.node import Node
from geometry_msgs.msg import Twist


class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            Twist,
            'cmd_vel',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        self.port_name = '/dev/ttyUSB0'  
        self.baud_rate =115200
        self.ser = None           

        try:
            self.ser = serial.Serial(self.port_name, self.baud_rate, timeout=0.1)
            self.get_logger().info(f'Serial port {self.port_name} opened successfully.')
        except serial.SerialException as e:
            self.get_logger().error(f'Failed to open serial port {self.port_name}: {e}')
         
    def listener_callback(self, msg):
        # If you push 'u' key, 'u' key let linear.x 0.5. -> let arduino turn on LED.
        # If you push 'm' key, 'm' key let linear.x -0.5. -> let arduino turn off LED. 
        self.get_logger().info('I heard: "%s"' % msg.linear.x)
        if self.ser and self.ser.is_open:
            if msg.linear.x >= 0:
                command = 'a'
                self.ser.write(command.encode())
                self.get_logger().debug(f'Sent serial command: {command}')
            elif msg.linear.x < 0:
                command = 'b'
                self.ser.write(command.encode())
                self.get_logger().debug(f'Sent serial command: {command}')


def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
