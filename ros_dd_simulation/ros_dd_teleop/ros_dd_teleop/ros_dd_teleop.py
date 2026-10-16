import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import sys
import select
import tty
import termios

# 선속도 및 각속도 상수 설정
LINEAR_SPEED = 0.5  # m/s
ANGULAR_SPEED = 1.0 # rad/s
MSG = """
로봇 제어
---------------------------
A : 좌회전 (Turn Left)
D : 우회전 (Turn Right)
W : 전진 (Forward)
S : 후진 (Backward)
Spacebar/K : 정지 (Stop)
CTRL-C to quit
"""

class ASDWTeleop(Node):
    def __init__(self):
        super().__init__('asdw_teleop_node')
        # 🌟 로봇 제어 토픽에 맞는 Publisher 생성 🌟
        # Harmonic DiffDrive receives /cmd_vel through ros_gz_bridge.
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
        self.settings = self.save_terminal_settings()
        self.get_logger().info(MSG)
        
        self.timer = self.create_timer(0.1, self.publish_twist)
        self.twist_msg = Twist()
        self.key = ''
        
    def save_terminal_settings(self):
        return termios.tcgetattr(sys.stdin)

    def restore_terminal_settings(self, settings):
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
        
    def get_key(self, settings):
        tty.setraw(sys.stdin.fileno())
        rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
        if rlist:
            key = sys.stdin.read(1)
        else:
            key = ''
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
        return key

    def update_twist(self):
        self.key = self.get_key(self.settings)
        
        linear_x = 0.0
        angular_z = 0.0
        
        if self.key == 'w':
            linear_x = LINEAR_SPEED
        elif self.key == 's':
            linear_x = -LINEAR_SPEED
        elif self.key == 'a':
            angular_z = ANGULAR_SPEED
        elif self.key == 'd':
            angular_z = -ANGULAR_SPEED
        elif self.key == ' ' or self.key == 'k': # 스페이스바 또는 k는 정지
            linear_x = 0.0
            angular_z = 0.0
        elif self.key == '\x03':  # Ctrl+C
            raise InterruptedError

        self.twist_msg.linear.x = linear_x
        self.twist_msg.angular.z = angular_z
        
    def publish_twist(self):
        try:
            self.update_twist()
            self.publisher_.publish(self.twist_msg)
        except InterruptedError:
            self.get_logger().info("Teleop node shutting down...")
            self.restore_terminal_settings(self.settings)
            rclpy.shutdown()
            
def main(args=None):
    rclpy.init(args=args)
    node = ASDWTeleop()
    try:
        rclpy.spin(node)
    except Exception as e:
        node.get_logger().error(f"Node caught exception: {e}")
    finally:
        if rclpy.ok():
             node.restore_terminal_settings(node.settings)
        node.destroy_node()

if __name__ == '__main__':
    main()