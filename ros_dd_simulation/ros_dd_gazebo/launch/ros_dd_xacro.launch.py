"""Run ros_dd with ROS 2 Jazzy and Gazebo Harmonic."""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    share = get_package_share_directory('ros_dd_gazebo')
    description_share = get_package_share_directory('ros_dd_description')
    gz_share = get_package_share_directory('ros_gz_sim')
    use_sim_time = LaunchConfiguration('use_sim_time')
    world = LaunchConfiguration('world')
    model = PathJoinSubstitution([description_share, 'urdf', 'ros_dd.xacro'])
    return LaunchDescription([
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        DeclareLaunchArgument('world', default_value=os.path.join(share, 'worlds', 'ros_dd.world')),
        DeclareLaunchArgument('gui_config', default_value=os.path.join(share, 'config', 'gui.config')),
        DeclareLaunchArgument('gz_args', default_value='-r',
                              description='Gazebo flags; use "-r -s" for server only'),
        SetEnvironmentVariable('GZ_SIM_RESOURCE_PATH', os.pathsep.join([
            os.path.join(share, 'models'), os.path.dirname(description_share),
            os.environ.get('GZ_SIM_RESOURCE_PATH', '')])),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(gz_share, 'launch', 'gz_sim.launch.py')),
            launch_arguments={'gz_args': [LaunchConfiguration('gz_args'), ' --gui-config "',
                                          LaunchConfiguration('gui_config'), '" "', world, '"']}.items()),
        Node(package='robot_state_publisher', executable='robot_state_publisher',
             parameters=[{'use_sim_time': use_sim_time,
                          'robot_description': ParameterValue(Command(['xacro ', model]), value_type=str)}],
             output='screen'),
        Node(package='ros_gz_sim', executable='create',
             arguments=['-world', 'default', '-name', 'ros_dd_robot',
                        '-topic', 'robot_description', '-x', '0', '-y', '0.5', '-z', '0.05'],
             output='screen'),
        Node(package='ros_gz_bridge', executable='parameter_bridge',
             parameters=[{'config_file': os.path.join(share, 'config', 'bridge.yaml'),
                          'use_sim_time': use_sim_time}], output='screen'),
    ])
