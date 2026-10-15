"""Publish two USB RGB streams and one Astra depth stream."""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def string_parameter(name):
    return ParameterValue(LaunchConfiguration(name), value_type=str)


def bool_parameter(name):
    return ParameterValue(LaunchConfiguration(name), value_type=bool)


def generate_launch_description():
    camera1_device = string_parameter('camera1_device')
    camera2_device = string_parameter('camera2_device')
    depth_camera_name = LaunchConfiguration('depth_camera_name')

    return LaunchDescription([
        DeclareLaunchArgument('camera1_device', default_value='/dev/video0'),
        DeclareLaunchArgument('camera2_device', default_value='/dev/video2'),
        DeclareLaunchArgument('depth_camera_name', default_value='depth_camera'),
        DeclareLaunchArgument('publish_depth_tf', default_value='true'),

        # Keep the existing first-camera publisher API, but give its output an
        # unambiguous name alongside camera 2 and the depth camera.
        Node(
            package='ros_cv',
            executable='cam_pub',
            name='rgb_camera_1',
            output='screen',
            parameters=[{'camera_device': camera1_device}],
            remappings=[('video_frames', '/camera1/image/compressed')],
        ),
        Node(
            package='ros_cv_2',
            executable='cam_pub',
            name='rgb_camera_2',
            output='screen',
            parameters=[{'camera_device': camera2_device}],
            remappings=[('camera2/image/compressed', '/camera2/image/compressed')],
        ),

        # The Astra also exposes color and IR streams. Disable them here so
        # this bring-up has exactly two RGB images and one depth image.
        Node(
            package='astra_camera',
            executable='astra_camera_node',
            namespace=depth_camera_name,
            name='camera',
            output='screen',
            parameters=[{
                'camera_name': string_parameter('depth_camera_name'),
                'enable_color': False,
                'enable_depth': True,
                'enable_ir': False,
                'enable_point_cloud': False,
                'enable_colored_point_cloud': False,
                'depth_registration': False,
                'depth_width': 640,
                'depth_height': 480,
                'depth_fps': 30,
                'depth_qos': 'default',
                'depth_camera_info_qos': 'default',
                'publish_tf': bool_parameter('publish_depth_tf'),
                'tf_publish_rate': 10.0,
                'connection_delay': 100,
            }],
        ),
    ])
