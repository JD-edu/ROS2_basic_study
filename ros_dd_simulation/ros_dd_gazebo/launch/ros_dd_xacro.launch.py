import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch.actions import SetEnvironmentVariable
# launch.substitutions에서 Command를 임포트합니다.
from launch.substitutions import Command 
# launch_ros.parameter_descriptions는 더 이상 필요하지 않습니다.

def generate_launch_description():
    pkg_name = 'ros_dd_gazebo'
    pkg_share_dir = get_package_share_directory(pkg_name)
    gazebo_ros_share_dir = get_package_share_directory('gazebo_ros')

    # ====================================================================
    # 1. Xacro 파일 경로 정의 및 로봇 설명 매개변수 설정 (최종 수정)
    # ====================================================================
    
    xacro_file_name = 'ros_dd.xacro' 
    xacro_path = PathJoinSubstitution([pkg_share_dir, 'urdf', xacro_file_name])

    # 🚀 Command 치환을 사용하여 Xacro를 처리하고 결과를 'robot_description'에 직접 할당합니다. 🚀
    robot_description_content = Command(['xacro ', xacro_path])

    # ROS 매개변수 'robot_description' 설정
    # LaunchConfiguration 치환 대신 Command 치환을 사용합니다.
    robot_description = {'robot_description': robot_description_content}

    # ====================================================================
    # 2. 필수 환경 변수 및 기타 설정 (변경 없음)
    # ====================================================================

    model_path = os.path.join(pkg_share_dir, 'models')
    set_model_path = SetEnvironmentVariable(
        name='GAZEBO_MODEL_PATH',
        value=[model_path, os.path.pathsep, os.environ.get('GAZEBO_MODEL_PATH', '')]
    )
    
    world_file = PathJoinSubstitution([pkg_share_dir, 'worlds', 'ros_dd.world'])

    # ====================================================================
    # 3. 노드 실행 (변경 없음)
    # ====================================================================

    # Gazebo 서버 실행
    start_gazebo_server = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(gazebo_ros_share_dir, 'launch', 'gzserver.launch.py')
        ]),
        launch_arguments={
            'world': world_file,
            'paused': 'false',
        }.items(),
    )

    # Gazebo 클라이언트 실행
    start_gazebo_client = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(gazebo_ros_share_dir, 'launch', 'gzclient.launch.py')
        ])
    )

    # 로봇의 기구학적 관계(TF)를 발행하는 노드
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[robot_description] 
    )

    # 모델 스폰 노드 실행
    spawn_robot_node = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-entity', 'ros_dd_robot',                
            '-topic', 'robot_description',            
            '-robot_namespace', '/',                  
            '-x', '0.0',                              
            '-y', '0.5',                              
            '-z', '0.2'                               
        ],
        output='screen'
    )

    return LaunchDescription([
        set_model_path, 
        start_gazebo_server,
        start_gazebo_client,
        robot_state_publisher_node,
        spawn_robot_node,
    ])