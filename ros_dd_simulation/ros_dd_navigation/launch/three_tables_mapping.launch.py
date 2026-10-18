"""Create a three-table map with Cartographer, without AMCL or Nav2."""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction, IncludeLaunchDescription, OpaqueFunction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

from ros_dd_navigation.launch_checks import assert_mode_available


def _check_mode(context):
    start_simulation = LaunchConfiguration('start_simulation').perform(context).lower()
    assert_mode_available('mapping', start_simulation in ('true', '1'))
    return []


def generate_launch_description():
    gazebo = get_package_share_directory('ros_dd_gazebo')
    slam = get_package_share_directory('ros_dd_cartographer')
    nav = get_package_share_directory('ros_dd_navigation')
    use_sim_time = LaunchConfiguration('use_sim_time')
    return LaunchDescription([
        DeclareLaunchArgument('gui', default_value='true'),
        DeclareLaunchArgument('use_rviz', default_value='true'),
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        DeclareLaunchArgument('start_simulation', default_value='true'),
        OpaqueFunction(function=_check_mode),
        GroupAction(actions=[IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(gazebo, 'launch', 'three_tables.launch.py')),
            condition=IfCondition(LaunchConfiguration('start_simulation')),
            launch_arguments={'gui': LaunchConfiguration('gui'),
                              'use_sim_time': use_sim_time}.items())]),
        GroupAction(actions=[IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(slam, 'launch', 'ros_dd_cartograph.launch.py')),
            launch_arguments={'configuration_basename': 'three_tables.lua',
                              'use_rviz': 'false', 'use_sim_time': use_sim_time}.items())]),
        Node(package='rviz2', executable='rviz2',
             condition=IfCondition(LaunchConfiguration('use_rviz')),
             arguments=['-d', os.path.join(nav, 'rviz', 'mapping.rviz')],
             parameters=[{'use_sim_time': use_sim_time}], output='screen'),
    ])
