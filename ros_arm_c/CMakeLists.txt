cmake_minimum_required(VERSION 3.8)
project(ros_arm_c)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

# Executable
add_executable(ros_arm_control src/ros_arm_bridge.cpp)
ament_target_dependencies(ros_arm_control rclcpp sensor_msgs std_msgs)

# Install Executables
install(TARGETS
  ros_arm_control
  DESTINATION lib/${PROJECT_NAME}
)

# Install Folders (URDF, Launch, Meshes, RViz)
install(DIRECTORY launch urdf meshes
  DESTINATION share/${PROJECT_NAME}
)

ament_package()