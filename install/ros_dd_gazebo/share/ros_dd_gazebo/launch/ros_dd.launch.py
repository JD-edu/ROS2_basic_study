import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch.actions import SetEnvironmentVariable
from launch_ros.parameter_descriptions import ParameterValue # 매개변수 값 처리를 위해 필요

def generate_launch_description():
    # 패키지 경로 분리
    gazebo_pkg_name = 'ros_dd_gazebo'
    description_pkg_name = 'ros_dd_description'

    gazebo_pkg_share_dir = get_package_share_directory(gazebo_pkg_name)
    description_pkg_share_dir = get_package_share_directory(description_pkg_name)
    gazebo_ros_share_dir = get_package_share_directory('gazebo_ros')

    # ====================================================================
    # 1. URDF 파일 경로 정의 및 로봇 설명 매개변수 설정
    # ====================================================================
    
    # 🌟 독립 패키지(ros_dd_description) 내의 URDF 파일 경로 지정 🌟
    urdf_path = os.path.join(description_pkg_share_dir, 'urdf', 'ros_dd.urdf')

    # 순수 URDF 파일을 읽어 robot_description 매개변수로 설정
    try:
        with open(urdf_path, 'r') as infp:
            robot_desc_data = infp.read()
    except EnvironmentError:
        # 파일이 없을 경우 예외 처리
        print(f"ERROR: Cannot find URDF file at {urdf_path}")
        exit(1)

    # ROS 매개변수 'robot_description'에 URDF 파일 내용 설정
    robot_description = {'robot_description': robot_desc_data}

    # ====================================================================
    # 2. 필수 환경 변수 및 기타 설정
    # ====================================================================

    # Gazebo 모델 패스 설정: ros_dd_description의 메쉬 및 모델도 인지할 수 있도록 두 경로 모두 추가
    gazebo_model_path = os.path.join(gazebo_pkg_share_dir, 'models')
    description_model_path = description_pkg_share_dir # package://ros_dd_description/mesh... 등의 참조를 위한 경로

    set_model_path = SetEnvironmentVariable(
        name='GAZEBO_MODEL_PATH',
        value=[
            gazebo_model_path, os.path.pathsep,
            description_model_path, os.path.pathsep,
            os.environ.get('GAZEBO_MODEL_PATH', '')
        ]
    )
    
    # 월드 파일 경로 설정 (ros_dd_gazebo 패키지 내부 유지)
    world_file = PathJoinSubstitution([gazebo_pkg_share_dir, 'worlds', 'ros_dd.world'])

    # ====================================================================
    # 3. 노드 실행 (Gazebo 서버/클라이언트, Robot State Publisher, Model Spawner)
    # ====================================================================

    # Gazebo 서버 실행 (월드 로드)
    start_gazebo_server = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(gazebo_ros_share_dir, 'launch', 'gzserver.launch.py')
        ]),
        launch_arguments={
            'world': world_file,
            'paused': 'false',
        }.items(),
    )

    # Gazebo 클라이언트 실행 (GUI)
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
        parameters=[robot_description] # robot_description 매개변수를 사용
    )

    # 모델 스폰 노드 실행 (URDF를 Gazebo로 로드)
    spawn_robot_node = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-entity', 'ros_dd_robot',                # Gazebo 내에서 로봇의 이름
            '-topic', 'robot_description',            # 로봇 모델 설명이 포함된 ROS 매개변수 이름
            '-robot_namespace', '/',                  # 로봇 네임스페이스
            '-x', '0.0',                              # 스폰할 위치 X 좌표
            '-y', '0.5',                              # 스폰할 위치 Y 좌표
            '-z', '0.2'                               # 스폰할 위치 Z 좌표
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