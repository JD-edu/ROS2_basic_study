"""Start the Arduino lidar bridge and a configured RViz viewer."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    """Expose serial settings and allow either component to run separately."""
    share = Path(get_package_share_directory('diy_lidar'))
    return LaunchDescription([
        DeclareLaunchArgument('port', default_value='/dev/ttyUSB0',
                              description='Arduino USB serial device'),
        DeclareLaunchArgument('baud', default_value='115200',
                              description='Serial baud rate'),
        DeclareLaunchArgument('frame_id', default_value='laser_frame',
                              description='Scan frame and RViz fixed frame'),
        DeclareLaunchArgument('use_bridge', default_value='true',
                              description='Start the serial bridge'),
        DeclareLaunchArgument('use_rviz', default_value='true',
                              description='Open RViz'),
        Node(
            package='diy_lidar', executable='lidar_bridge', output='screen',
            condition=IfCondition(LaunchConfiguration('use_bridge')),
            parameters=[{
                'port': ParameterValue(LaunchConfiguration('port'), value_type=str),
                'baud': ParameterValue(LaunchConfiguration('baud'), value_type=int),
                'frame_id': ParameterValue(
                    LaunchConfiguration('frame_id'), value_type=str),
                'topic': '/scan',
            }]),
        Node(
            package='rviz2', executable='rviz2', output='screen',
            condition=IfCondition(LaunchConfiguration('use_rviz')),
            arguments=['-d', str(share / 'rviz' / 'lidar.rviz'),
                       '-f', LaunchConfiguration('frame_id')]),
    ])
