cmake_minimum_required(VERSION 3.8)
project(ros_cv_center_c)

# C++ 표준 설정 (OpenCV와 ROS 2에서 일반적으로 권장되는 C++17)
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# ==============================================================================
# 1. 의존성 찾기 (find_package)
# ==============================================================================
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# ROS 2 메시지 및 OpenCV 관련
# cv_bridge, sensor_msgs는 카메라 직접 접근 방식에서는 필요 없지만,
# 혹시 모를 확장성을 위해 최소한의 find_package는 유지할 수 있습니다.
# 여기서는 카메라 직접 접근 방식에 맞게 필수적인 것만 남깁니다.

# OpenCV 찾기
find_package(OpenCV REQUIRED)

# 사용자 정의 메시지 패키지 찾기
find_package(cv_msg REQUIRED)


# ==============================================================================
# 2. 퍼블리셔 노드 (color_detector_node)
#    - 기능: 카메라 캡처, OpenCV 처리, 중심점 발행
# ==============================================================================

# 실행 파일 정의
add_executable(center_pub src/center_pub.cpp)

# 실행 파일의 종속성 (rclcpp, cv_msg) 정의
# OpenCV는 ament_target_dependencies가 아닌 target_link_libraries로 링크됩니다.
ament_target_dependencies(center_pub
  rclcpp
  cv_msg
)

# OpenCV 라이브러리 링크
target_link_libraries(center_pub
  ${OpenCV_LIBRARIES}     # OpenCV의 모든 컴포넌트 링크
)

# 빌드 시 헤더 검색 경로에 OpenCV와 메시지 빌드 경로 추가
target_include_directories(center_pub PRIVATE
  ${OpenCV_INCLUDE_DIRS}
  $<BUILD_INTERFACE:${cv_msg_INCLUDE_DIRS}>
)

# ==============================================================================
# 3. 구독자 노드 (center_point_subscriber_node)
#    - 기능: 중심점 토픽 구독, 콘솔 출력
# ==============================================================================

# 실행 파일 정의
add_executable(center_sub src/center_sub.cpp)

# 구독자 노드 종속성 정의
ament_target_dependencies(center_sub
  rclcpp
  cv_msg
)

# ==============================================================================
# 4. 설치 (install)
# ==============================================================================

# 두 실행 파일을 ROS 설치 디렉토리에 복사
install(TARGETS
  center_pub
  center_sub
  DESTINATION lib/${PROJECT_NAME}
)

# ==============================================================================
# 5. 패키지 내보내기 (export)
# ==============================================================================
ament_package()