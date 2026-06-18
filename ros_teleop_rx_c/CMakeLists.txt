cmake_minimum_required(VERSION 3.8)
project(ros_teleop_rx_c)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED) 


# Find libserial
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSERIAL REQUIRED libserial)

# Include directories
include_directories(${LIBSERIAL_INCLUDE_DIRS})

# Create executable for serial reader node
add_executable(led_control 
  src/led_control.cpp
)

# Link dependencies
ament_target_dependencies(led_control
  rclcpp
  std_msgs
  geometry_msgs
)

# Link libserial
target_link_libraries(led_control ${LIBSERIAL_LIBRARIES})
target_compile_options(led_control PRIVATE ${LIBSERIAL_CFLAGS_OTHER})


# Install targets
install(TARGETS
  led_control
  DESTINATION lib/${PROJECT_NAME}
)

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
