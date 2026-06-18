# ROS2_study

## 개요 (Overview)

본 저장소는 ROS2 Humble 환경에서의 학습을 위한 교육용 패키지 모음입니다. Ubuntu 22.04 LTS 환경에서 ROS2의 기본 개념부터 고급 기능까지 단계별로 학습할 수 있도록 구성되어 있습니다. 토픽과 서비스 통신, 영상 처리, 로봇 제어, 시뮬레이션 및 SLAM 등 ROS2의 핵심 기능들을 실습을 통해 익힐 수 있습니다.

## 시스템 요구사항 (System Requirements)

- **운영체제**: Ubuntu 22.04 LTS
- **ROS 버전**: ROS 2 Humble Hawksbill
- **Python 버전**: Python 3.10+
- **C++ 표준**: C++17
- **추가 의존성**: OpenCV, Gazebo, RViz2, Cartographer

## 패키지 목록 및 설명 (Package List and Descriptions)

| 패키지명                      | 언어          | 설명                                     | 상태   |
| ----------------------------- | ------------- | ---------------------------------------- | ------ |
| **cv_msg**              | Interface     | 커스텀 메시지 및 서비스 정의 패키지      | 완료   |
| **ros_agv**             | Python        | 기초 2바퀴 로봇 노드 패키지              | 미완성 |
| **ros_arm**             | Python        | 기초 5축 로봇암 노드 패키지              | 미완성 |
| **ros_cv**              | Python        | OpenCV 기반 영상 토픽 pub/sub 패키지     | 완료   |
| **ros_cv_c**            | C++           | ros_cv의 C++ 구현 버전                   | 완료   |
| **ros_cv_center**       | Python        | 적색 영역 중심점 검출 및 전송 패키지     | 완료   |
| **ros_cv_center_c**     | C++           | ros_cv_center의 C++ 구현 버전            | 완료   |
| **ros_dd**              | URDF/Launch   | 4바퀴 로봇 URDF RViz 시각화 패키지        | 완료   |
| **ros_dd_c**            | URDF/Launch   | ros_dd C++ version                | 완료   |
| **ros_dd_simulation**   | Meta package  | ros_dd simulation meta package    | 완료   |
| **ros_dd_cartographer** | Launch/Config | ros_dd_gazebo용 Cartographer SLAM 패키지 | 완료   |
| **ros_dd_gazebo**       | Launch/URDF   | ros_dd 로봇 Gazebo 시뮬레이션 패키지     | 완료   |
| **ros_dd_navigation**   | Launch/Config | ros_dd_gazebo 자율주행 네비게이션 패키지 | 개발중   |
| **ros_dd_teleop**       | Python        | ros_dd_gazebo AWSD 키 조종 패키지        | 완료   |
| **ros_motor_srv**       | Python        | 아두이노 모터 서비스 제어 패키지         | 완료   |
| **ros_motor_srv_c**     | C++           | ros_motor_srv의 C++ 구현 버전            | 완료   |
| **ros_serial**          | Python        | ROS2 시리얼 통신 패키지                  | 완료   |
| **ros_serial_c**        | C++           | ros_serial의 C++ 구현 버전               | 완료   |
| **ros_srv**             | Python        | 두 수 덧셈 서비스 예제 패키지            | 완료   |
| **ros_srv_c**           | C++           | ros_srv의 C++ 구현 버전                  | 완료   |
| **ros_teleop_rx**       | Python        | cmd_vel 토픽 수신 패키지                 | 완료   |
| **ros_teleop_rx_c**     | C++           | ros_teleop_rx의 C++ 구현 버전            | 완료   |
| **ros_topic**           | Python        | 기본 문자열 토픽 발행 예제 패키지        | 완료   |
| **ros_topic_c**         | C++           | ros_topic의 C++ 구현 버전                | 완료   |

## 패키지 분류 (Package Categories)

### 1. 기초 예제 (Basic Examples)

ROS 2의 핵심 통신 방식을 학습할 수 있는 기초 패키지들입니다.

- **토픽 통신 예제**

  - `ros_topic` / `ros_topic_c`: 기본 문자열 발행/구독
  - `ros_teleop_rx` / `ros_teleop_rx_c`: cmd_vel 토픽 수신
- **서비스 예제**

  - `ros_srv` / `ros_srv_c`: 두 수 덧셈 서비스
  - `ros_motor_srv` / `ros_motor_srv_c`: 아두이노 모터 제어 서비스
- **시리얼 통신 예제**

  - `ros_serial` / `ros_serial_c`: 시리얼 포트 통신

### 2. 영상 처리 (Computer Vision)

OpenCV를 활용한 영상 처리 및 컴퓨터 비전 관련 패키지들입니다.

- **기본 영상 처리**

  - `ros_cv` / `ros_cv_c`: OpenCV 영상 토픽 통신
- **객체 검출**

  - `ros_cv_center` / `ros_cv_center_c`: 적색 영역 중심점 검출

### 3. 로봇 제어 (Robot Control)

다양한 형태의 로봇 제어를 위한 패키지들입니다.

- **이동 로봇**

  - `ros_agv`: 2바퀴 로봇 제어 (개발 중)
- **매니퓰레이터**

  - `ros_arm`: 5축 로봇암 제어 (개발 중)
- **원격 조종**

  - `ros_dd_teleop`: 키보드 기반 로봇 조종

### 4. 시뮬레이션 및 SLAM (Simulation & SLAM)

가상 환경에서의 로봇 시뮬레이션 및 SLAM 구현 패키지들입니다.

- **시각화**

  - `ros_dd`: RViz를 통한 URDF 시각화
- **시뮬레이션**

  - `ros_dd_gazebo`: Gazebo 시뮬레이션 환경
- **SLAM**

  - `ros_dd_cartographer`: Cartographer 기반 SLAM
- **자율주행**

  - `ros_dd_navigation`: Navigation2 기반 자율주행

### 5. 커스텀 메시지 (Custom Messages)

사용자 정의 메시지 및 서비스 인터페이스입니다.

- **cv_msg**: 영상 처리 관련 커스텀 메시지 정의
  - 중심점 좌표 메시지
  - 모터 제어 서비스
  - add 2 integers service 

## 설치 방법 (Installation)

### 1. 저장소 클론

```bash
cd ~/ros2_ws/src
git clone https://github.com/JD-edu/ROS2_study.git
```

### 2. 의존성 설치(NOT tested)

```bash
cd ~/ros2_ws
rosdep install --from-paths src --ignore-src -r -y
```

### 3. 빌드
Before build copy all files and fildes into /home/jdedu/ros2_ws/src. 

```bash
cd ~/ros2_ws
colcon build
```
You may install libserial-dev. If you get such message when you build ROS2 package.
```bash
--- stderr: ros_serial_c

CMake Error at /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:603 (message):

  A required package was not found

Call Stack (most recent call first):

  /usr/share/cmake-3.22/Modules/FindPkgConfig.cmake:825 (_pkg_check_modules_internal)

  CMakeLists.txt:14 (pkg_check_modules)
```
Install libserial-dev
```bash
sudo apt update
sudo apt install libserial-dev
```

### 4. 환경 설정

```bash
source ~/ros2_ws/install/setup.bash
```

## 사용 방법 (Usage)

### 기본 예제 실행

```bash
# 터미널 1: 문자열 발행자 실행
ros2 run ros_topic talker

# 터미널 2: 문자열 구독자 실행
ros2 run ros_topic listener
```

### 영상 처리 예제 실행

```bash
# 영상 발행자 실행
ros2 run ros_cv image_publisher

# 적색 영역 검출기 실행
ros2 run ros_cv_center center_detector
```

### 시뮬레이션 환경 실행

# Run Gazebo 
```bash
# Gazebo 시뮬레이션 실행
ros2 launch ros_dd_gazebo ros_dd_xacro.launch.py
```
If gazebo is not running, execute following command.

```bash
source /usr/share/gazebo/setup.sh
```

# 원격 조종 실행
```bash
ros2 run ros_dd_teleop asdw_teleop
```

# Run cartographer to make map
```bash
ros2 launch ros_dd_cartographer ros_dd_cartographer.launch.py use_sim_time:=True
```
You need to move robot until map is fully scanned. 
# Make map 
```bash
ros2 run nav2_map_server map_saver_cli -f ~/map
```
Above command save map files(map.pgm, map.yaml) at ~/ folder. 

### SLAM 실행
```bash
# Gazebo 실행
ros2 launch ros_dd_gazebo ros_dd_xacro.launch.py
```

# Cartographer SLAM 실행
```bash
ros2 launch ros_dd_cartographer cartographer.launch.py
```

# 자율주행 실행
```bash
ros2 launch ros_dd_navigation navigation.launch.py use_sim_time:=True map:=$HOME/map.yaml
```

## 저장소 구조 (Repository Structure)

```
ROS2_study/
├── cv_msg/                    # 커스텀 메시지 패키지
├── ros_agv/                   # 2바퀴 로봇 패키지 (개발 중)
├── ros_arm/                   # 5축 로봇암 패키지 (개발 중)
├── ros_cv/                    # OpenCV 영상 처리 (Python)
├── ros_cv_c/                  # OpenCV 영상 처리 (C++)
├── ros_cv_center/             # 적색 영역 검출 (Python)
├── ros_cv_center_c/           # 적색 영역 검출 (C++)
├── ros_dd/                    # URDF 시각화 (Python)
├── ros_dd_c/                  # URDF 시각화(C++)
├── ros_dd_simulation/         # ros_dd meta package
  ├── ros_dd_cartographer/     # Cartographer SLAM
  ├── ros_dd_gazebo/           # Gazebo 시뮬레이션
  ├── ros_dd_navigation/       # 자율주행 네비게이션
  └── ros_dd_teleop/           # 키보드 조종
├── ros_motor_srv/             # 모터 서비스 제어 (Python)
├── ros_motor_srv_c/           # 모터 서비스 제어 (C++)
├── ros_serial/                # 시리얼 통신 (Python)
├── ros_serial_c/              # 시리얼 통신 (C++)
├── ros_srv/                   # 기본 서비스 (Python)
├── ros_srv_c/                 # 기본 서비스 (C++)
├── ros_teleop_rx/             # 원격조종 수신 (Python)
├── ros_teleop_rx_c/           # 원격조종 수신 (C++)
├── ros_topic/                 # 기본 토픽 (Python)
├── ros_topic_c/               # 기본 토픽 (C++)
└── README.md                  # 본 문서
```

## 라이선스 (License)

본 프로젝트는 교육 목적으로 제작되었습니다. 자유롭게 학습 및 연구 목적으로 사용하실 수 있습니다.

## 문의사항 (Contact)

프로젝트에 대한 질문이나 제안사항이 있으시면 이슈(Issue)를 통해 문의해 주세요.

---

**참고**: 본 저장소의 패키지들은 ROS 2 Humble 환경에서 테스트되었습니다. 다른 ROS 2 배포판에서는 일부 수정이 필요할 수 있습니다.
