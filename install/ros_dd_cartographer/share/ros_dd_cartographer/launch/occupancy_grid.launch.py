# dd_cartographer/launch/occupancy_grid.launch.py

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # Gazebo 시뮬레이션 시간 사용 여부
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    # 맵 해상도
    resolution = LaunchConfiguration('resolution', default='0.05')
    # 맵 발행 주기
    publish_period_sec = LaunchConfiguration('publish_period_sec', default='1.0')

    return LaunchDescription([
        # Launch Argument 선언
        DeclareLaunchArgument(
            'resolution',
            default_value=resolution,
            description='Resolution of a grid cell in the published occupancy grid'),

        DeclareLaunchArgument(
            'publish_period_sec',
            default_value=publish_period_sec,
            description='OccupancyGrid publishing period'),

        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true', # 시뮬레이션 환경이므로 기본값을 true로 설정
            description='Use simulation (Gazebo) clock if true'),

        # Cartographer Occupancy Grid Node
        Node(
            package='cartographer_ros',
            executable='cartographer_occupancy_grid_node',
            name='cartographer_occupancy_grid_node',
            output='screen',
            parameters=[{'use_sim_time': use_sim_time}],
            arguments=['-resolution', resolution, '-publish_period_sec', publish_period_sec]),
    ])