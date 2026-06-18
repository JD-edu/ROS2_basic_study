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

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
import serial 

class JointStateSubscriber(Node):
    def __init__(self):
        super().__init__('joint_state_subscriber')
        self.subscriber = self.create_subscription(
            JointState,
            '/joint_states',
            self.joint_state_callback,
            10
        )
        self.pub_count = 0
        self.ser = serial.Serial("/dev/ttyACM0", baudrate = 115200, parity=serial.PARITY_NONE, 
                               stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, 
                               timeout=0.3)
   
    def joint_state_callback(self, msg):
        # Process the received joint state message
        base = msg.position[0]*(180/3.14)
        shoulder = msg.position[1]*(180/3.14)
        forearm = msg.position[2]*(180/3.14)
        upperarm = msg.position[3]*(180/3.14)
        self.pub_count +=1
        if self.pub_count > 4: 
            #print(msg.position[0], msg.position[1], msg.position[2], msg.position[3],msg.position[4])
            cmd = "a"+str(int(base))+"b"+str(int(shoulder))+"c"+str(int(forearm))+"d"+str(int(upperarm))+"e\n"
            print(cmd)
            self.ser.write(cmd.encode())
            self.pub_count = 0

def main(args=None):
    rclpy.init(args=args)

    joint_state_subscriber = JointStateSubscriber()

    rclpy.spin(joint_state_subscriber)

    rclpy.shutdown()

if __name__ == '__main__':
    main()