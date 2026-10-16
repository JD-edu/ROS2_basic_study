"""Start the Harmonic three-table world and the URDF robot at the origin."""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PythonExpression


def generate_launch_description():
    share = get_package_share_directory('ros_dd_gazebo')
    return LaunchDescription([
        DeclareLaunchArgument('gui', default_value='true'),
        DeclareLaunchArgument('gui_config', default_value=os.path.join(
            share, 'config', 'three_tables_gui.config')),
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(share, 'launch', 'ros_dd.launch.py')),
            launch_arguments={
                'world': os.path.join(share, 'worlds', 'three_tables.world'),
                'world_name': 'three_tables',
                'gui_config': LaunchConfiguration('gui_config'),
                'x': '0', 'y': '0', 'z': '0.05', 'yaw': '0',
                'use_sim_time': LaunchConfiguration('use_sim_time'),
                'gz_args': PythonExpression([
                    "'-r' if '", LaunchConfiguration('gui'),
                    "'.lower() in ('true', '1') else '-r -s'"]),
            }.items()),
    ])
