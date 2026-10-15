"""테이블 월드, SLAM, Nav2와 하네스 속도 게이트를 함께 실행합니다."""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # 1. 설치된 ROS 패키지에서 launch와 설정 파일의 위치를 찾습니다.
    gazebo_dir = get_package_share_directory('ros_dd_gazebo')
    cartographer_dir = get_package_share_directory('ros_dd_cartographer')
    navigation_dir = get_package_share_directory('ros_dd_navigation')

    nav2_dir = get_package_share_directory('nav2_bringup')

    # 2. 터미널에서 바꿀 수 있는 옵션을 선언합니다.
    # 예: ros2 launch ... gui:=false
    gui_argument = DeclareLaunchArgument('gui', default_value='true')
    rviz_argument = DeclareLaunchArgument('use_rviz', default_value='true')
    clock_argument = DeclareLaunchArgument('use_sim_time', default_value='true')
    gate_argument = DeclareLaunchArgument(
        'use_velocity_gate', default_value='true',
        description='Start the velocity gate; false when running it in a separate terminal')
    harness_root_argument = DeclareLaunchArgument(
        'harness_root', default_value='/home/robo/robot_harness',
        description='slam_harness 소스가 들어 있는 폴더')
    nav_params_argument = DeclareLaunchArgument(
        'nav_params',
        default_value=os.path.join(navigation_dir, 'config', 'three_tables_nav2.yaml'))

    # LaunchConfiguration은 터미널에서 받은 옵션 값을 사용한다는 뜻입니다.
    params_argument = DeclareLaunchArgument('params_file', default_value=LaunchConfiguration('nav_params'))
    gui = LaunchConfiguration('gui')
    use_rviz = LaunchConfiguration('use_rviz')
    use_sim_time = LaunchConfiguration('use_sim_time')
    harness_root = LaunchConfiguration('harness_root')
    nav_params = LaunchConfiguration('params_file')

    # 3. 다른 launch 파일을 불러와 테이블 3개와 로봇을 생성합니다.
    simulation = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_dir, 'launch', 'three_tables.launch.py')),
        launch_arguments={'gui': gui}.items())

    # 4. Cartographer 노드를 직접 실행합니다.
    # 기존 navigation.launch.py나 Nav2의 기본 launch는 불러오지 않습니다.
    # SLAM이 지도와 map -> odom TF를 제공하므로 AMCL/map_server는 실행하지 않습니다.
    slam = Node(
        package='cartographer_ros', executable='cartographer_node',
        name='cartographer_node', output='screen',
        parameters=[{'use_sim_time': use_sim_time}],
        arguments=[
            '-configuration_directory', os.path.join(cartographer_dir, 'config'),
            '-configuration_basename', 'three_tables.lua',
        ],
        remappings=[('scan', 'scan'), ('odom', 'odom')])

    # Cartographer의 submap을 Nav2가 사용하는 /map 격자 지도로 변환합니다.
    occupancy_grid = Node(
        package='cartographer_ros', executable='cartographer_occupancy_grid_node',
        name='cartographer_occupancy_grid_node', output='screen',
        parameters=[{'use_sim_time': use_sim_time}],
        arguments=['-resolution', '0.05', '-publish_period_sec', '1.0'])

    # 5. 하네스 소스 폴더에서 Python 모듈을 실행합니다.
    # 터미널의 "python3 -m slam_harness.velocity_gate"와 같은 역할입니다.
    # 게이트는 Nav2/미세 정렬 중 하나의 속도를 선택해 로봇의 /cmd_vel로 보냅니다.
    # 별도 터미널에서 게이트를 실행했다면 use_velocity_gate:=false로 중복 실행을 막습니다.
    # 자연어 미션 자체는 별도 터미널에서 실행합니다.
    velocity_gate = ExecuteProcess(
        cmd=['/usr/bin/python3', '-m', 'slam_harness.velocity_gate',
             '--ros-args', '-p', ['use_sim_time:=', use_sim_time]],
        cwd=harness_root,
        condition=IfCondition(LaunchConfiguration('use_velocity_gate')),
        output='screen')

    # 6. Nav2 노드를 하나씩 선언합니다.
    # package: ROS 패키지 이름, executable: 실행할 프로그램 이름
    # parameters: YAML 설정 + Gazebo 시계 사용(use_sim_time)
    # remappings: Nav2의 속도 출력 이름을 바꿔 게이트를 거치게 합니다.
    controller = Node(
        package='nav2_controller', executable='controller_server',
        name='controller_server', output='screen',
        parameters=[nav_params, {'use_sim_time': use_sim_time}],
        remappings=[('cmd_vel', '/slam_harness/nav_cmd_vel')])

    # 목적지까지 이동할 경로를 계산합니다.
    planner = Node(
        package='nav2_planner', executable='planner_server',
        name='planner_server', output='screen',
        parameters=[nav_params, {'use_sim_time': use_sim_time}],
        remappings=[('cmd_vel', '/slam_harness/nav_cmd_vel')])

    # 경로를 다듬는 기능을 제공합니다.
    smoother = Node(
        package='nav2_smoother', executable='smoother_server',
        name='smoother_server', output='screen',
        parameters=[nav_params, {'use_sim_time': use_sim_time}],
        remappings=[('cmd_vel', '/slam_harness/nav_cmd_vel')])

    # 회전, 후진 등 Nav2의 복구 동작을 제공합니다.
    behaviors = Node(
        package='nav2_behaviors', executable='behavior_server',
        name='behavior_server', output='screen',
        parameters=[nav_params, {'use_sim_time': use_sim_time}],
        remappings=[('cmd_vel', '/slam_harness/nav_cmd_vel')])

    # 하네스의 NavigateToPose 요청을 받아 계획/주행/복구를 조율합니다.
    navigator = Node(
        package='nav2_bt_navigator', executable='bt_navigator',
        name='bt_navigator', output='screen',
        parameters=[nav_params, {'use_sim_time': use_sim_time}],
        remappings=[('cmd_vel', '/slam_harness/nav_cmd_vel')])

    # 7. Nav2 노드들은 프로세스 실행 후 별도의 활성화 절차가 필요합니다.
    # lifecycle_manager가 아래 이름의 노드들을 자동으로 설정하고 활성화합니다.
    lifecycle_manager = Node(
        package='nav2_lifecycle_manager', executable='lifecycle_manager',
        name='lifecycle_manager_navigation', output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
            'autostart': True,
            'node_names': [
                'controller_server',
                'planner_server',
                'smoother_server',
                'behavior_server',
                'bt_navigator',
            ],
        }])

    # 8. RViz는 Nav2가 제공하는 화면 설정 파일만 재사용합니다.
    # launch를 불러오는 것은 아니며 use_rviz:=false로 끌 수 있습니다.
    rviz = Node(
        package='rviz2', executable='rviz2', name='rviz2', output='screen',
        arguments=['-d', os.path.join(nav2_dir, 'rviz', 'nav2_default_view.rviz')],
        parameters=[{'use_sim_time': use_sim_time}],
        condition=IfCondition(use_rviz))

    # 9. 위에서 선언한 실행 항목을 ROS launch에 전달합니다.
    # 이 목록은 각 노드의 준비 완료를 기다리는 순차 실행 코드가 아닙니다.
    return LaunchDescription([
        gui_argument,
        rviz_argument,
        clock_argument,
        gate_argument,
        harness_root_argument,
        nav_params_argument,
        params_argument,
        simulation,
        slam,
        occupancy_grid,
        velocity_gate,
        controller,
        planner,
        smoother,
        behaviors,
        navigator,
        lifecycle_manager,
        rviz,
    ])
