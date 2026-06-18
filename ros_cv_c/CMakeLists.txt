cmake_minimum_required(VERSION 3.8)
project(ros_cv_c)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)

# 퍼블리셔 실행 파일 생성
add_executable(cam_pub src/cam_pub.cpp)
ament_target_dependencies(cam_pub rclcpp sensor_msgs cv_bridge OpenCV)

# 서브스크라이버 실행 파일 생성
add_executable(cam_sub src/cam_sub.cpp)
ament_target_dependencies(cam_sub rclcpp sensor_msgs cv_bridge OpenCV)

# 퍼블리셔(cam_pub)에 OpenCV 라이브러리 연결
#target_link_libraries(cam_pub
#  OpenCV::opencv
#)

# 서브스크라이버(cam_sub)에 OpenCV 라이브러리 연결
#target_link_libraries(cam_sub
#  OpenCV::opencv
#)

# 실행 파일 설치
install(TARGETS
  cam_pub
  cam_sub
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
