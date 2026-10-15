"""Start one independent publisher process per camera."""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'camera2_device', default_value='/dev/video2',
            description='Second camera capture device (different from /dev/video0)'),
        Node(package='ros_cv', executable='cam_pub', output='screen'),
        Node(
            package='ros_cv_2', executable='cam_pub', output='screen',
            parameters=[{'camera_device': ParameterValue(
                LaunchConfiguration('camera2_device'), value_type=str)}]),
    ])
