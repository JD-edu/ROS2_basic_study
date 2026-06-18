cmake_minimum_required(VERSION 3.8)
project(ros_topic_c)

# 컴파일러 옵션 설정
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 의존성 패키지 찾기
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 퍼블리셔 실행 파일 생성
add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

# 서브스크라이버 실행 파일 생성
add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

# 실행 파일 설치
install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})

# 테스트 설정 (선택사항)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # 다음 줄은 패키지에 setup.cfg가 없는 경우 주석 처리
  # ament_lint_auto_find_test_dependencies()
endif()

# 패키지 설정 완료
ament_package()