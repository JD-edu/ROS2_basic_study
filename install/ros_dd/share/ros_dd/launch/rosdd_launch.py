# urdf_rviz_launch.py
import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # 로봇 설명 파일 경로
    urdf_file_name = 'ros_dd.urdf'
    urdf_file_path = os.path.join(
        get_package_share_directory('ros_dd'),'urdf',
        urdf_file_name
    )

        # RViz 설정 파일 경로
    rviz_config_file = os.path.join(
        get_package_share_directory('ros_dd'), 'rviz', 'ros_dd.rviz'
    )

    # launch description 생성
    return LaunchDescription([
        # 로봇 상태 퍼블리셔
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'robot_description': open(urdf_file_path).read()}]
        ),

        # 조인트 상태 퍼블리셔 GUI
        Node(
            package='joint_state_publisher_gui',
            executable='joint_state_publisher_gui',
            name='joint_state_publisher_gui',
            output='screen',
        ),

        # RViz 실행
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            output='screen',
            arguments=['-d', rviz_config_file]
        ),
    ])

if __name__ == '__main__':
    generate_launch_description()
