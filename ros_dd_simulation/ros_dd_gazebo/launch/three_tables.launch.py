"""Gazebo에 테이블 3개 월드와 ros_dd 로봇을 생성합니다."""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # 1. 설치된 패키지 안에서 필요한 파일 경로를 만듭니다.
    gazebo_ros_dir = get_package_share_directory('gazebo_ros')
    gazebo_dir = get_package_share_directory('ros_dd_gazebo')
    description_dir = get_package_share_directory('ros_dd_description')

    world_file = os.path.join(gazebo_dir, 'worlds', 'three_tables.world')
    urdf_file = os.path.join(description_dir, 'urdf', 'ros_dd.urdf')
    with open(urdf_file, 'r') as file:
        robot_description = file.read()

    # 2. gui:=false로 실행하면 Gazebo 창을 생략합니다.
    gui_argument = DeclareLaunchArgument('gui', default_value='true')
    gui = LaunchConfiguration('gui')

    # 3. Gazebo 서버: 물리 시뮬레이션과 ROS 통신을 담당합니다.
    gazebo_server = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros_dir, 'launch', 'gzserver.launch.py')),
        launch_arguments={
            'world': world_file,
            'paused': 'false',
        }.items())

    # 4. Gazebo 클라이언트: 화면을 보여줍니다. gui가 true일 때만 실행합니다.
    gazebo_client = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros_dir, 'launch', 'gzclient.launch.py')),
        condition=IfCondition(gui))

    # 5. URDF를 바탕으로 로봇 부품 사이의 TF를 발행합니다.
    state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{
            'robot_description': robot_description,
            'use_sim_time': True,
        }])

    # 6. robot_description 토픽의 URDF를 읽어 Gazebo에 로봇을 생성합니다.
    # SLAM 좌표와 맞추기 위해 world (0, 0), yaw=0에서 시작합니다.
    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        output='screen',
        arguments=[
            '-entity', 'ros_dd_robot',
            '-topic', 'robot_description',
            '-x', '0',
            '-y', '0',
            '-z', '0.2',
        ])

    # 7. 이 launch는 월드와 로봇만 실행합니다. SLAM/Nav2는 통합 launch에서 실행합니다.
    return LaunchDescription([
        gui_argument,
        gazebo_server,
        gazebo_client,
        state_publisher,
        spawn_robot,
    ])
