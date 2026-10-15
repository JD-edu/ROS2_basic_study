# Three Tables 하네스 사용법

기존 `ros_dd_navigation/launch/navigation.launch.py`는 저장 지도와 AMCL로 주행하는 기존 방식으로 유지합니다.
새 `three_tables_navigation.launch.py`는 그 파일이나 Nav2의 navigation_launch.py/bringup_launch.py를 불러오지 않습니다.
Cartographer와 Nav2 노드를 `Node(...)`로 하나씩 선언한 독립 구성입니다.
월드와 로봇을 만드는 `three_tables.launch.py`만 포함합니다.

## 두 방식의 차이

| 구분 | 기존 navigation.launch.py 기반 운영 | 새 three_tables_navigation.launch.py |
|---|---|---|
| 지도 | 미리 제작·저장한 지도 로딩 | 실행 중 Cartographer가 생성 |
| 위치 추정 | AMCL | Cartographer |
| 목적지 결정 | 사용자의 목표 지정 등 | 하네스가 로컬 LLM으로 방문 순서 생성 |
| 실제 이동 | Nav2 | Nav2 |

이번 three tables는 처음 제안한 AI 하네스 구성으로, **실시간 SLAM + LLM 방문 계획 + Nav2 이동**을 사용합니다.
LLM은 좌표나 주행 속도를 만들지 않습니다. 등록된 테이블 이름의 순서만 생성합니다.
하네스는 locations.yaml에서 좌표를 조회하고 이동 결과를 확인합니다.
AI 계획 기능 자체는 저장 지도 + AMCL에서도 사용할 수 있지만, 이 launch는 실시간 SLAM 실습용입니다.

## 1. 빌드

```bash
cd /home/robo/ros2_ws
source /opt/ros/humble/setup.bash
colcon build --packages-select ros_dd_description ros_dd_gazebo ros_dd_cartographer ros_dd_navigation
source install/setup.bash
```

## 2. 월드·SLAM·Nav2·게이트 실행

```bash
source /opt/ros/humble/setup.bash
source /home/robo/ros2_ws/install/setup.bash
ros2 launch ros_dd_navigation three_tables_navigation.launch.py gui:=true use_rviz:=true
```

기존 Gazebo/SLAM/Nav2를 같은 도메인에서 중복 실행하지 않습니다.
화면 없이 실행하려면 `gui:=false use_rviz:=false`로 설정합니다.
이 launch는 이동 준비만 하며, LLM 미션은 별도 터미널에서 시작합니다.

월드와 로봇만 보고 싶다면 통합 launch 대신 다음 명령을 사용합니다.

```bash
ros2 launch ros_dd_gazebo three_tables.launch.py gui:=true
```

월드 전용 launch에는 SLAM·Nav2·속도 게이트가 없으므로 이동 미션을 실행할 수 없습니다.

## 3. 로컬 Qwen3 8B로 방문 계획 실행

이 머신의 llama.cpp 서버가 http://127.0.0.1:8080/v1에서 qwen3-8b로 실행 중인 구성을 사용합니다.
서버 확인:

```bash
curl -fsS http://127.0.0.1:8080/health
curl -fsS http://127.0.0.1:8080/v1/models
```

먼저 계획만 확인합니다. 이 명령은 로봇을 움직이지 않습니다.

```bash
cd /home/robo/robot_harness
/usr/bin/python3 -m slam_harness.main '테이블 1번 들렀다가 2번으로 가' \
  --base-url http://127.0.0.1:8080/v1 --model qwen3-8b --dry-run
```

기대하는 계획: `{"waypoints":["table_1","table_2"]}`.
새 터미널에서 실제 이동을 실행합니다.

```bash
cd /home/robo/robot_harness
source /opt/ros/humble/setup.bash
source /home/robo/ros2_ws/install/setup.bash
/usr/bin/python3 -m slam_harness.main '테이블 1번 들렀다가 2번으로 가' \
  --base-url http://127.0.0.1:8080/v1 --model qwen3-8b \
  --alignment skip --ros-args -p use_sim_time:=true
```

`--alignment skip`은 미세 정렬을 생략하고 Nav2 방문만 수행합니다.
기본 optional은 정렬을 시도하지만 시간 초과를 경고로 기록하고 다음 방문을 진행합니다.
required는 정렬을 필수로 요구하며 실패하면 후퇴를 시도하고 미션을 중단합니다.

LLM 없이 실행 경로만 검증하려면:

```bash
/usr/bin/python3 -m slam_harness.main \
  --plan-json '{"waypoints":["table_1","table_2"]}' \
  --alignment skip --ros-args -p use_sim_time:=true
```

## 코드 읽는 순서

launch 파일의 한국어 번호 주석 순서대로 읽으면 됩니다.

| 변수 | 역할 |
|---|---|
| simulation | 테이블 월드와 로봇 생성 |
| slam | Cartographer로 지도와 위치 추정 |
| occupancy_grid | submap을 Nav2가 사용하는 /map 지도로 변환 |
| velocity_gate | 하네스의 속도 선택·정지 감시 |
| controller | 경로를 따라갈 속도 계산 |
| planner | 경로 계산 |
| smoother | 경로를 다듬는 기능 제공 |
| behaviors | 회전·후진 등 Nav2 복구 기능 |
| navigator | NavigateToPose 요청 처리와 주행 조율 |
| lifecycle_manager | 위 Nav2 서버들을 설정·활성화 |
| rviz | 지도와 로봇 상태 표시 |

`Node`의 package는 패키지, executable은 실행 프로그램, parameters는 설정입니다.
`DeclareLaunchArgument`는 터미널 옵션을 선언하고 `LaunchConfiguration`은 그 값을 사용합니다.
`remappings`는 토픽 등의 ROS 이름을 바꿉니다. 이 구성은 Nav2 속도를 게이트 입력으로 연결합니다.
`ExecuteProcess`는 robot_harness 폴더에서 Python 모듈을 실행합니다.
`LaunchDescription`은 실행할 항목 목록이며 준비 완료를 기다리는 순차 명령은 아닙니다.
Nav2의 lifecycle_manager가 서버를 configure/activate하여 주행 준비를 합니다.

```text
자연어 → Qwen3 → 테이블 이름 순서 → 하네스 → NavigateToPose → Nav2
라이다 → Cartographer → /map, map→odom TF ────────────────────┘
Nav2 속도 → /slam_harness/nav_cmd_vel → 게이트 → /cmd_vel → 로봇
```

경로를 다듬는 smoother_server는 속도 스무더와 다른 기능입니다.
이번 구성은 별도 velocity_smoother 노드 없이 controller/behaviors 출력을 게이트로 연결합니다.
AMCL/map_server는 실행하지 않습니다. RViz는 Nav2의 화면 설정 파일만 재사용합니다.

## 파일 위치와 옵션

- ros_dd_gazebo/worlds/three_tables.world: 월드
- ros_dd_gazebo/launch/three_tables.launch.py: 월드·로봇 실행
- ros_dd_cartographer/config/three_tables.lua: SLAM 설정
- ros_dd_navigation/config/three_tables_nav2.yaml: Nav2 설정
- ros_dd_navigation/launch/three_tables_navigation.launch.py: 독립 통합 launch
- /home/robo/robot_harness/slam_harness: LLM·미션 정책·ROS 스킬·게이트
- /home/robo/robot_harness/slam_harness/config/locations.yaml: 테이블 접근·정렬·후퇴 좌표

옵션은 gui, use_rviz, use_sim_time, harness_root, params_file입니다.
이전 nav_params 옵션도 params_file의 기본값 별칭으로 지원합니다.
시뮬레이션에서는 use_sim_time:=true를 유지하고 모든 관련 터미널에서 같은 ROS_DOMAIN_ID를 사용합니다.
좌표는 world (0,0), yaw=0에서 시작하는 SLAM에 맞춰져 있습니다. 다른 지도로 바꾸면 좌표를 다시 등록해야 합니다.
