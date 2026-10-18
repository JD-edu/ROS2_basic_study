"""Navigate the three-table world using a saved map and AMCL, without SLAM."""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction, IncludeLaunchDescription, OpaqueFunction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

from ros_dd_navigation.launch_checks import assert_mode_available, validate_map_file


def _start_navigation(context):
    # Validate before launching Gazebo or any navigation node.
    map_path = validate_map_file(LaunchConfiguration('map').perform(context))
    start_simulation = LaunchConfiguration('start_simulation').perform(context).lower()
    assert_mode_available('saved-map navigation', start_simulation in ('true', '1'))
    gazebo = get_package_share_directory('ros_dd_gazebo')
    nav = get_package_share_directory('ros_dd_navigation')
    use_sim_time = LaunchConfiguration('use_sim_time')
    return [
        GroupAction(actions=[IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(gazebo, 'launch', 'three_tables.launch.py')),
            condition=IfCondition(LaunchConfiguration('start_simulation')),
            launch_arguments={'gui': LaunchConfiguration('gui'),
                              'use_sim_time': use_sim_time}.items())]),
        GroupAction(actions=[IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(nav, 'launch', 'navigation.launch.py')),
            launch_arguments={'use_localization': 'true', 'map': map_path,
                              'use_rviz': LaunchConfiguration('use_rviz'),
                              'use_sim_time': use_sim_time,
                              'rviz_software_rendering': LaunchConfiguration('rviz_software_rendering'),
                              'params_file': LaunchConfiguration('params_file')}.items())]),
    ]


def generate_launch_description():
    nav = get_package_share_directory('ros_dd_navigation')
    return LaunchDescription([
        DeclareLaunchArgument('map', description='Required: saved three-table map YAML path'),
        DeclareLaunchArgument('gui', default_value='true'),
        DeclareLaunchArgument('use_rviz', default_value='true'),
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        DeclareLaunchArgument('start_simulation', default_value='true'),
        DeclareLaunchArgument('rviz_software_rendering', default_value='false'),
        DeclareLaunchArgument('nav_params', default_value=os.path.join(
            nav, 'config', 'three_tables_nav2.yaml')),
        DeclareLaunchArgument('params_file', default_value=LaunchConfiguration('nav_params')),
        OpaqueFunction(function=_start_navigation),
    ])
