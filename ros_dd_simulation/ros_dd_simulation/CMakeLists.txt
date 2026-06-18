cmake_minimum_required(VERSION 3.8)
project(ros_dd_simulation)

find_package(ament_cmake REQUIRED)

# 메타 패키지용 빌드 명령. 실제 코드를 빌드하지 않고, ROS 시스템에 메타 패키지로 인식하게 합니다.
ament_package()