"""Run the three-table world, Cartographer SLAM, Nav2 and optional RViz."""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    gazebo = get_package_share_directory('ros_dd_gazebo')
    slam = get_package_share_directory('ros_dd_cartographer')
    nav = get_package_share_directory('ros_dd_navigation')
    use_sim_time = LaunchConfiguration('use_sim_time')
    return LaunchDescription([
        DeclareLaunchArgument('gui', default_value='true'),
        DeclareLaunchArgument('use_rviz', default_value='true'),
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        DeclareLaunchArgument('nav_params', default_value=os.path.join(
            nav, 'config', 'three_tables_nav2.yaml')),
        DeclareLaunchArgument('params_file', default_value=LaunchConfiguration('nav_params')),
        GroupAction(actions=[IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(gazebo, 'launch', 'three_tables.launch.py')),
            launch_arguments={'gui': LaunchConfiguration('gui'),
                              'use_sim_time': use_sim_time}.items())]),
        GroupAction(actions=[IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(slam, 'launch', 'ros_dd_cartograph.launch.py')),
            launch_arguments={'configuration_basename': 'three_tables.lua',
                              'use_rviz': 'false', 'use_sim_time': use_sim_time}.items())]),
        GroupAction(actions=[IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(nav, 'launch', 'navigation.launch.py')),
            launch_arguments={'use_localization': 'false',
                              'use_rviz': LaunchConfiguration('use_rviz'),
                              'use_sim_time': use_sim_time,
                              'params_file': LaunchConfiguration('params_file')}.items())]),
    ])
