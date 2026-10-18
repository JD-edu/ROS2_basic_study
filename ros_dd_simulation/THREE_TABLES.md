# Three Tables: 지도 작성과 저장 지도 내비게이션

ROS 2 Jazzy / Gazebo Harmonic. 하네스·LLM과 오브젝트 등록 코드는 변경하지 않았습니다.

| 단계 | launch | /map 발행자 | map → odom | Nav2 |
|---|---|---|---|---|
| 지도 작성 | three_tables_mapping.launch.py | Cartographer | Cartographer | 실행 안 함 |
| 내비게이션 | three_tables_navigation.launch.py | map_server | AMCL | 실행 |

각 launch는 기본적으로 Gazebo와 로봇도 실행합니다. 이전 단계는 `Ctrl+C`로 종료한 뒤
다음 단계를 시작합니다. 기존 Cartographer/AMCL/Nav2가 발견되면 새 launch가 중단됩니다.
다른 launch를 동시에 시작하는 경쟁 상황까지 막는 잠금 기능은 아닙니다.

각 터미널에서 먼저 환경을 불러옵니다.

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
```

## 1. 지도 작성

```bash
ros2 launch ros_dd_navigation three_tables_mapping.launch.py
```

Gazebo, Cartographer, 지도 작성용 RViz만 실행합니다. AMCL, map_server, Nav2는
실행하지 않습니다. 별도 터미널에서 다음으로 로봇을 이동해 테이블 세 개와 네 벽을
충분히 관측합니다.

```bash
ros2 run ros_dd_teleop asdw_teleop
```

W/A/S/D로 조작하고 Space 또는 K로 정지합니다. 지도 작성용 RViz에는 내비게이션
목표 도구와 코스트맵 그룹이 없습니다.

## 2. 지도 저장

로봇을 정지시킨 뒤, **Cartographer가 실행 중인 상태에서** 별도 터미널에서 저장합니다.
기존 육각형 지도와 혼동하지 않도록 전용 경로를 사용합니다.

```bash
mkdir -p ~/ros2_ws/maps/three_tables
ros2 run nav2_map_server map_saver_cli \
  -f ~/ros2_ws/maps/three_tables/map \
  --ros-args -p use_sim_time:=true -p save_map_timeout:=10.0
```

`~/ros2_ws/maps/three_tables/map.yaml`과 `map.pgm`이 생성됩니다.
저장 성공을 확인하고 teleop과 지도 작성 launch를 `Ctrl+C`로 종료합니다.

## 3. 저장 지도 내비게이션

```bash
ros2 launch ros_dd_navigation three_tables_navigation.launch.py \
  map:=$HOME/ros2_ws/maps/three_tables/map.yaml
```

Gazebo, map_server, AMCL, Nav2, 내비게이션용 RViz가 실행됩니다.
**Cartographer는 실행하지 않습니다.** `map` 인수는 필수입니다. 지도 YAML 또는
참조 이미지가 없으면 시뮬레이터와 내비게이션 노드를 시작하기 전에 중단합니다.
기존 육각형 지도를 기본값으로 불러오지 않습니다.

1. **2D Pose Estimate**로 저장 지도 안에서 로봇의 현재 위치와 방향을 지정합니다.
2. LiDAR 점이 저장 지도의 벽·테이블 윤곽과 맞는지 확인합니다.
3. **2D Goal Pose**로 목적지를 지정합니다.
4. **Global Planner**, **Local Planner**를 켜면 경로와 코스트맵이 보입니다.

지도 좌표와 Gazebo 월드 좌표가 같다고 가정하지 않습니다. 확인되지 않은 `(0, 0)`을
AMCL 초기 위치로 자동 설정하지 않습니다. 초기 위치 설정 전에는 `navigation_startup`이 대기합니다.
AMCL이 최신 TF를 제공한 뒤 Nav2를 활성화하므로 초기 위치 입력이 늦어져도
planner의 60초 시작 제한 때문에 전체 활성화가 중단되지 않습니다.
`Nav2 ready: navigation goals can now be sent.` 로그 후 목표를 지정합니다.
초기 위치 자동화와 오브젝트 좌표 등록은 좌표 검증 후 별도 작업으로 적용합니다.

좌표 입력 노드도 사용할 수 있습니다.

```bash
ros2 run ros_dd_nav2 goto_pose --ros-args -p use_sim_time:=true
```

`x y [yaw_degrees]`를 반복 입력합니다. `cancel`은 이동 취소, `q`는 입력 노드 종료입니다.
좌표는 저장 지도의 `map` 기준입니다. 장애물인 테이블 중심은 목표로 지정하지 않습니다.

## 옵션

- `gui:=false`: Gazebo GUI 비활성화
- `use_rviz:=false`: RViz 비활성화
- `start_simulation:=false`: 이미 실행 중인 **같은 세 테이블 월드**의 Gazebo 재사용
- `use_sim_time:=true`: 기본값. 관련 노드에서 동일하게 사용
- 내비게이션의 `params_file:=/absolute/path/to/nav2.yaml`: Nav2 설정 교체

Gazebo를 재사용하더라도 Cartographer와 내비게이션은 동시에 실행하지 않습니다.

## 향후 하네스 연결점

저장 지도 내비게이션은 `/navigate_to_pose` 액션과 `/goal_pose` 토픽을 제공합니다.
현재 속도 출력은 Nav2 velocity_smoother → `/cmd_vel` → Gazebo입니다.
velocity_gate와 LLM은 실행하지 않습니다. 이후 하네스 단계에서 등록된 접근 좌표를
Nav2 액션으로 전달하고, 필요한 경우 속도 게이트를 별도로 연결할 수 있습니다.
