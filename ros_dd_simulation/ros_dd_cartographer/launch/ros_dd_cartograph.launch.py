# dd_cartographer/launch/cartographer.launch.py

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node


def generate_launch_description():
    # =================================================================
    # 1. Launch Arguments (인수 선언)
    # =================================================================
    
    pkg_share_dir = get_package_share_directory('ros_dd_cartographer')

    # 시뮬레이션 환경이므로 기본값을 'true'로 설정합니다.
    use_sim_time = LaunchConfiguration('use_sim_time', default='true') 
    use_rviz = LaunchConfiguration('use_rviz', default='true')
    
    # 설정 파일 디렉토리
    cartographer_config_dir = LaunchConfiguration('cartographer_config_dir', 
                                                  default=os.path.join(pkg_share_dir, 'config'))
    
    # 사용할 LUA 설정 파일 이름 (이전에 작성한 파일 이름)
    configuration_basename = LaunchConfiguration('configuration_basename',
                                                 default='ros_dd_cartographer.lua')

    # 맵 해상도 (occupancy_grid.launch.py로 전달됨)
    resolution = LaunchConfiguration('resolution', default='0.05')
    publish_period_sec = LaunchConfiguration('publish_period_sec', default='1.0')

    # Rviz 설정 파일 경로 (dd_cartographer/rviz/dd_cartographer.rviz 경로를 가정)
    rviz_config_dir = os.path.join(pkg_share_dir, 'rviz', 'ros_dd_cartographer.rviz')
    
    
    # =================================================================
    # 2. Actions (노드 및 포함)
    # =================================================================

    # 2-1. Cartographer SLAM Node
    cartographer_node = Node(
        package='cartographer_ros',
        executable='cartographer_node',
        name='cartographer_node',
        output='screen',
        parameters=[{'use_sim_time': use_sim_time}],
        arguments=['-configuration_directory', cartographer_config_dir,
                   '-configuration_basename', configuration_basename],
        remappings=[
            ('echoes', 'horizontal_laser_2d'),
            # 센서 토픽 리매핑 (URDF에서 설정한 토픽 이름과 일치)
            ('scan', 'scan'), 
            ('imu', 'imu/data'),
            ('odom', 'odom'),
        ]
    )

    # 2-2. Occupancy Grid Node 포함 (맵 빌더)
    occupancy_grid_include = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([pkg_share_dir, 'launch', 'occupancy_grid.launch.py'])
        ]),
        launch_arguments={'use_sim_time': use_sim_time, 
                          'resolution': resolution,
                          'publish_period_sec': publish_period_sec}.items(),
    )

    # 2-3. Rviz2 Node (조건부 실행)
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_dir],
        parameters=[{'use_sim_time': use_sim_time}],
        condition=IfCondition(use_rviz),
        output='screen')

    
    # =================================================================
    # 3. Launch Description 반환
    # =================================================================
    
    return LaunchDescription([
        # Argument 선언
        DeclareLaunchArgument(
            'cartographer_config_dir',
            default_value=cartographer_config_dir,
            description='Full path to config file to load'),
        DeclareLaunchArgument(
            'configuration_basename',
            default_value=configuration_basename,
            description='Name of lua file for cartographer'),
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'),
        DeclareLaunchArgument(
            'use_rviz',
            default_value='true',
            description='Whether to start RVIZ'),
        DeclareLaunchArgument(
            'resolution',
            default_value=resolution,
            description='Resolution of a grid cell in the published occupancy grid'),
        DeclareLaunchArgument(
            'publish_period_sec',
            default_value=publish_period_sec,
            description='OccupancyGrid publishing period'),
        
        # 노드 실행
        cartographer_node,
        occupancy_grid_include,
        rviz_node,
    ])