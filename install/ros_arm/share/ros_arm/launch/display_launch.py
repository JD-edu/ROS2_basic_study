
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

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='false')
    urdf = os.path.join(get_package_share_directory('ros_arm'), 'urdf', 'ros_arm.urdf')
    rviz_config = os.path.join(get_package_share_directory('ros_arm'), 'rviz', 'ros_arm.rviz')

    with open(urdf, 'r') as infp:
        robot_desc = infp.read()
   
    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='false',),
        Node(
	    package='robot_state_publisher',
	    executable='robot_state_publisher',
	    name='robot_state_publisher',
	    output='screen',
	    parameters=[{
		'use_sim_time': use_sim_time,
		'robot_description': robot_desc,
		'source_list': ['joint_1', 'joint_2', 'joint_3', 'joint_4','joint_5','joint_6'],
		'zeros': {
		    'joint_1': 1.5708,
		    'joint_2': 1.5708,
		    'joint_3': 1.5708,
		    'joint_4': 1.5708,
		    'joint_5': 0,
		    'joint_6': 0
		    }
	    }]
	    ),
        Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        output='screen',
        parameters=[{
        'use_sim_time': use_sim_time,
        'robot_description': robot_desc,
		'source_list': ['joint_1', 'joint_2', 'joint_3', 'joint_4','joint_5','joint_6'],
		'zeros': {
		    'joint_1': 1.5708,
		    'joint_2': 1.5708,
		    'joint_3': 1.5708,
		    'joint_4': 1.5708,
		    'joint_5': 0,
		    'joint_6': 0
		    }
	    }]
        ),
        Node(
            package='ros_arm',
            executable='ros_arm_control',
            name='ros_arm_controls',
            output='screen'
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            output='screen',
            arguments=['-d', os.path.join(get_package_share_directory('ros_arm'),'rviz','ros_arm.rviz')]
		),
    ])


if __name__ == '__main__':
    generate_launch_description()
