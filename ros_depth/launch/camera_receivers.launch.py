"""Start both JPEG receivers and the 16UC1 depth receiver."""

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros_cv',
            executable='cam_sub',
            name='camera1_image_subscriber',
            output='screen',
            remappings=[
                ('camera/image/compressed', '/camera1/image/compressed'),
            ],
        ),
        Node(
            package='ros_cv_2',
            executable='cam_sub',
            name='camera2_image_subscriber',
            output='screen',
            remappings=[
                ('camera2/image/compressed', '/camera2/image/compressed'),
            ],
        ),
        Node(
            package='ros_depth',
            executable='depth_sub',
            name='depth_image_subscriber',
            output='screen',
            parameters=[{
                'depth_topic': '/camera/depth/image_raw',
                'max_depth_mm': 5000,
            }],
        ),
    ])
