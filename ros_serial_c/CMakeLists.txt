cmake_minimum_required(VERSION 3.8)
project(ros_serial_c)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Find libserial
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSERIAL REQUIRED libserial)

# Include directories
include_directories(${LIBSERIAL_INCLUDE_DIRS})

# Create executable for serial reader node
add_executable(serial_pub 
  src/serial_pub.cpp
)

add_executable(serial_sub 
  src/serial_sub.cpp
)

# Link dependencies
ament_target_dependencies(serial_pub
  rclcpp
  std_msgs
)

# Link dependencies
ament_target_dependencies(serial_sub
  rclcpp
  std_msgs
)

# Link libserial
target_link_libraries(serial_pub ${LIBSERIAL_LIBRARIES})
target_compile_options(serial_pub PRIVATE ${LIBSERIAL_CFLAGS_OTHER})

target_link_libraries(serial_sub ${LIBSERIAL_LIBRARIES})
target_compile_options(serial_sub PRIVATE ${LIBSERIAL_CFLAGS_OTHER})

# Install targets
install(TARGETS
  serial_pub
  serial_sub
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
