"""Jazzy navigation with optional AMCL localization on a saved map."""
import os
from pathlib import Path

import yaml

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import Node
from launch_ros.descriptions import ParameterFile
from launch_ros.parameter_descriptions import ParameterValue
from nav2_common.launch import RewrittenYaml


def _validate_map(context):
    """Reject a missing map or image before starting localization nodes."""
    path = Path(LaunchConfiguration('map').perform(context)).expanduser()
    if not path.is_file():
        raise RuntimeError(f'Map YAML file does not exist: {path}')
    with path.open(encoding='utf-8') as stream:
        config = yaml.safe_load(stream)
    if not isinstance(config, dict) or not config.get('image'):
        raise RuntimeError(f'Map YAML has no image entry: {path}')
    image = Path(config['image']).expanduser()
    if not image.is_absolute():
        image = path.parent / image
    if not image.is_file():
        raise RuntimeError(f'Map image does not exist: {image}')
    return []


def _launch_rviz(context):
    """Allow a graphics-driver workaround limited to the RViz process."""
    software = LaunchConfiguration('rviz_software_rendering').perform(context).lower()
    env = {'LIBGL_ALWAYS_SOFTWARE': '1'} if software in ('true', '1') else {}
    return [Node(
        package='rviz2', executable='rviz2',
        arguments=['-d', LaunchConfiguration('rviz_config').perform(context)],
        parameters=[{'use_sim_time': LaunchConfiguration('use_sim_time')}],
        additional_env=env, output='screen')]


def generate_launch_description():
    share = get_package_share_directory('ros_dd_navigation')
    use_sim_time = LaunchConfiguration('use_sim_time')
    autostart = LaunchConfiguration('autostart')
    use_localization = LaunchConfiguration('use_localization')
    delayed_start = PythonExpression([
        "'", use_localization, "'.lower() in ('true', '1') and '",
        autostart, "'.lower() in ('true', '1')"])
    immediate_start = PythonExpression([
        "'", use_localization, "'.lower() not in ('true', '1') and '",
        autostart, "'.lower() in ('true', '1')"])
    params = ParameterFile(RewrittenYaml(
        source_file=LaunchConfiguration('params_file'),
        param_rewrites={'use_sim_time': use_sim_time}, convert_types=True))
    servers = [
        ('nav2_controller', 'controller_server'),
        ('nav2_smoother', 'smoother_server'),
        ('nav2_planner', 'planner_server'),
        ('nav2_behaviors', 'behavior_server'),
        ('nav2_bt_navigator', 'bt_navigator'),
        ('nav2_waypoint_follower', 'waypoint_follower'),
        ('nav2_velocity_smoother', 'velocity_smoother'),
    ]
    actions = [
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        DeclareLaunchArgument('autostart', default_value='true'),
        DeclareLaunchArgument('use_rviz', default_value='true'),
        DeclareLaunchArgument('rviz_config', default_value=os.path.join(share, 'rviz', 'navigation.rviz')),
        DeclareLaunchArgument('rviz_software_rendering', default_value='false',
                              description='Use CPU rendering for RViz graphics driver issues'),
        DeclareLaunchArgument('use_localization', default_value='true',
                              description='Disable when Cartographer provides map and map->odom'),
        DeclareLaunchArgument('map', default_value=os.path.join(share, 'maps', 'map.yaml')),
        DeclareLaunchArgument('params_file', default_value=os.path.join(share, 'config', 'nav2_params.yaml')),
        OpaqueFunction(function=_validate_map,
                       condition=IfCondition(LaunchConfiguration('use_localization'))),
        Node(package='nav2_map_server', executable='map_server', name='map_server',
             condition=IfCondition(LaunchConfiguration('use_localization')),
             parameters=[params, {'yaml_filename': LaunchConfiguration('map')}],
             remappings=[('/tf', 'tf'), ('/tf_static', 'tf_static')], output='screen'),
        Node(package='nav2_amcl', executable='amcl', name='amcl',
             condition=IfCondition(LaunchConfiguration('use_localization')),
             parameters=[params],
             remappings=[('/tf', 'tf'), ('/tf_static', 'tf_static')], output='screen'),
        Node(package='nav2_lifecycle_manager', executable='lifecycle_manager',
             name='lifecycle_manager_localization',
             condition=IfCondition(LaunchConfiguration('use_localization')),
             parameters=[{'use_sim_time': use_sim_time, 'autostart': autostart,
                          'node_names': ['map_server', 'amcl']}], output='screen'),
    ]
    for package, executable in servers:
        remaps = [('/tf', 'tf'), ('/tf_static', 'tf_static')]
        if executable in ('controller_server', 'behavior_server'):
            remaps.append(('cmd_vel', 'cmd_vel_nav'))
        elif executable == 'velocity_smoother':
            remaps.extend([('cmd_vel', 'cmd_vel_nav'), ('cmd_vel_smoothed', 'cmd_vel')])
        actions.append(Node(package=package, executable=executable, name=executable,
                            parameters=[params], remappings=remaps, output='screen'))
    actions.extend([
        Node(package='nav2_lifecycle_manager', executable='lifecycle_manager',
             name='lifecycle_manager_navigation', output='screen',
             parameters=[{'use_sim_time': use_sim_time,
                          'autostart': ParameterValue(immediate_start, value_type=bool),
                          'node_names': [name for _, name in servers]}]),
        Node(package='ros_dd_navigation', executable='start_navigation_when_localized',
             name='navigation_startup', condition=IfCondition(delayed_start),
             parameters=[{'use_sim_time': use_sim_time}], output='screen'),
        OpaqueFunction(function=_launch_rviz,
                       condition=IfCondition(LaunchConfiguration('use_rviz'))),
    ])
    return LaunchDescription(actions)
