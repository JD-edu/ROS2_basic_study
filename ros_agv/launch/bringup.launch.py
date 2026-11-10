"""Start the Arduino driver, robot TF publisher, and RViz."""
from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    """Use encoder joint states from the driver to visualize the robot."""
    share = Path(get_package_share_directory('ros_agv'))
    robot_description = (share / 'urdf' / 'ros_agv.urdf').read_text()
    return LaunchDescription([
        DeclareLaunchArgument(
            'serial_port', default_value='/dev/ttyUSB0',
            description='Arduino serial device'),
        Node(
            package='ros_agv', executable='ros_agv', output='screen',
            parameters=[{'serial_port': LaunchConfiguration('serial_port')}]),
        Node(
            package='robot_state_publisher', executable='robot_state_publisher',
            output='screen', parameters=[{'robot_description': robot_description}]),
        Node(
            package='rviz2', executable='rviz2', output='screen',
            arguments=['-d', str(share / 'rviz' / 'ros_agv.rviz')]),
    ])
