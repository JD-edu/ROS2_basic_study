import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, GroupAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node

def generate_launch_description():
    pkg_name = 'ros_dd_navigation'
    nav2_bringup_dir = get_package_share_directory('nav2_bringup')
    pkg_share_dir = get_package_share_directory(pkg_name)

    # 1. Launch Arguments 선언
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    map_yaml_file = LaunchConfiguration('map', default=os.path.join(pkg_share_dir, 'map.yaml'))
    params_file = LaunchConfiguration('params_file', default=os.path.join(pkg_share_dir, 'config', 'nav2_params.yaml'))
    
    # 2. Nav2 Bringup 실행
    # Nav2의 핵심 노드(AMCL, Planner, Controller, BT Navigator 등)를 실행합니다.
    nav2_bringup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(nav2_bringup_dir, 'launch', 'bringup_launch.py')
        ),
        launch_arguments={
            'map': map_yaml_file,
            'use_sim_time': use_sim_time,
            'params_file': params_file,
            'autostart': 'true',
            'namespace': '', # 네임스페이스 없이 실행
        }.items(),
    )
    
    # 3. Rviz2 실행 (Nav2 설정을 로드)
    # Nav2는 자체 Rviz 설정을 사용하므로 nav2_bringup에서 제공하는 파일을 사용합니다.
    rviz_config_dir = os.path.join(nav2_bringup_dir, 'rviz', 'nav2_default_view.rviz')
    
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_dir],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'),
        DeclareLaunchArgument(
            'map',
            default_value=map_yaml_file,
            description='Full path to map file to load'),
        DeclareLaunchArgument(
            'params_file',
            default_value=params_file,
            description='Full path to param file to load'),

        nav2_bringup,
        rviz_node,
    ])