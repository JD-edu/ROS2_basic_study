cmake_minimum_required(VERSION 3.8)
project(ros_motor_srv_c)

# C++ 표준 설정
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# ==============================================================================
# 1. 의존성 찾기 (find_package)
# ==============================================================================
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# 서비스 정의가 들어있는 cv_msg 패키지를 찾습니다.
find_package(cv_msg REQUIRED)

# LibSerial을 찾기 위해 PkgConfig를 사용합니다. (LibSerial 사용을 위해 필수)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSERIAL REQUIRED libserial)


# ==============================================================================
# 2. 서버 노드 정의 및 링크 (serial 사용)
# ==============================================================================

# 서버 노드 실행 파일 정의
add_executable(server src/server.cpp)

# 서버 노드의 ROS 및 커스텀 메시지 종속성
ament_target_dependencies(server
  rclcpp
  cv_msg  # 서비스 헤더 파일 접근을 위해 필수
)

# Include directories
include_directories(${LIBSERIAL_INCLUDE_DIRS})

# Link libserial
target_link_libraries(server ${LIBSERIAL_LIBRARIES})
target_compile_options(server PRIVATE ${LIBSERIAL_CFLAGS_OTHER})


# 서버 노드에만 LibSerial 라이브러리 링크 적용
#target_link_libraries(add_two_ints_server
#  ${LIBSERIAL_LDFLAGS}           # 라이브러리 경로
#  ${LIBSERIAL_LIBRARIES}         # 라이브러리 이름 (-lserial)
#  ${CMAKE_THREAD_LIBS_INIT}      # 쓰레드 라이브러리
#)

# 서버 노드에만 LibSerial 헤더 경로 추가
#target_include_directories(add_two_ints_server PRIVATE
#  ${LIBSERIAL_INCLUDE_DIRS}      # LibSerial 헤더 경로
#  $<BUILD_INTERFACE:${cv_msg_INCLUDE_DIRS}> # cv_msg 헤더 경로
#)

# ==============================================================================
# 3. 클라이언트 노드 정의 및 링크 (serial 미사용)
# ==============================================================================

# 클라이언트 노드 실행 파일 정의
add_executable(client src/client.cpp)

# 클라이언트 노드의 종속성 (LibSerial 관련 설정은 제외)
ament_target_dependencies(client
  rclcpp
  cv_msg
)


# ==============================================================================
# 4. 설치 (install)
# ==============================================================================

# 두 실행 파일을 ROS 설치 디렉토리에 복사
install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME}
)


# ==============================================================================
# 5. 패키지 내보내기 (export)
# ==============================================================================
ament_package()