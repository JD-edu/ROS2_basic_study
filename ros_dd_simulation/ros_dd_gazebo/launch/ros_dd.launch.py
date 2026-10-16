"""Launch the Harmonic simulation directly from the saved URDF."""
import os
from pathlib import Path
import shlex

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    ExecuteProcess,
    OpaqueFunction,
    SetEnvironmentVariable,
    Shutdown,
)
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def _launch_gazebo(context):
    """Split optional CLI flags into arguments without using a shell."""
    return [ExecuteProcess(
        cmd=[
            'gz', 'sim',
            *shlex.split(LaunchConfiguration('gz_args').perform(context)),
            '--gui-config', LaunchConfiguration('gui_config').perform(context),
            LaunchConfiguration('world').perform(context),
            '--force-version', '8',
        ],
        name='gazebo',
        output='screen',
        on_exit=Shutdown(reason='Gazebo exited'),
    )]


def generate_launch_description():
    gazebo_share = Path(get_package_share_directory('ros_dd_gazebo'))
    description_share = Path(get_package_share_directory('ros_dd_description'))
    urdf_path = description_share / 'urdf' / 'ros_dd.urdf'
    robot_description = urdf_path.read_text(encoding='utf-8')
    use_sim_time = LaunchConfiguration('use_sim_time')

    resource_path = SetEnvironmentVariable(
        'GZ_SIM_RESOURCE_PATH', os.pathsep.join([
            str(gazebo_share / 'models'),
            str(description_share.parent),
            os.environ.get('GZ_SIM_RESOURCE_PATH', ''),
        ]))
    plugin_path = SetEnvironmentVariable(
        'GZ_SIM_SYSTEM_PLUGIN_PATH', os.pathsep.join([
            os.environ.get('GZ_SIM_SYSTEM_PLUGIN_PATH', ''),
            os.environ.get('LD_LIBRARY_PATH', ''),
        ]))

    gazebo = OpaqueFunction(function=_launch_gazebo)

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{
            'use_sim_time': use_sim_time,
            'robot_description': ParameterValue(robot_description, value_type=str),
        }],
        output='screen',
    )

    spawn_robot = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=[
            '-world', LaunchConfiguration('world_name'), '-name', 'ros_dd_robot',
            '-topic', 'robot_description',
            '-x', LaunchConfiguration('x'), '-y', LaunchConfiguration('y'),
            '-z', LaunchConfiguration('z'), '-Y', LaunchConfiguration('yaw'),
        ],
        output='screen',
    )

    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{
            'config_file': str(gazebo_share / 'config' / 'bridge.yaml'),
            'use_sim_time': use_sim_time,
        }],
        output='screen',
    )

    return LaunchDescription([
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        DeclareLaunchArgument('world_name', default_value='default'),
        DeclareLaunchArgument('x', default_value='0'),
        DeclareLaunchArgument('y', default_value='0.5'),
        DeclareLaunchArgument('z', default_value='0.05'),
        DeclareLaunchArgument('yaw', default_value='0'),
        DeclareLaunchArgument('world', default_value=str(gazebo_share / 'worlds' / 'ros_dd.world')),
        DeclareLaunchArgument('gui_config', default_value=str(gazebo_share / 'config' / 'gui.config')),
        DeclareLaunchArgument('gz_args', default_value='-r',
                              description='Gazebo flags; use "-r -s" for server only'),
        resource_path,
        plugin_path,
        gazebo,
        robot_state_publisher,
        spawn_robot,
        bridge,
    ])
