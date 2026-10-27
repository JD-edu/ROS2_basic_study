# ros_dd_simulation — ROS 2 Jazzy / Gazebo Harmonic

Ubuntu 24.04, ROS 2 Jazzy, Gazebo Harmonic(`gz sim`) 환경입니다.
로봇 모델은 `ros_dd_description/urdf/ros_dd.urdf`를 직접 읽어 실행합니다.
Gazebo Classic / `gazebo_ros`는 사용하지 않습니다.

## 설치 및 빌드

```bash
sudo apt-get update
sudo apt-get install ros-jazzy-ros-gz ros-jazzy-navigation2 ros-jazzy-nav2-bringup ros-jazzy-cartographer-ros
cd /home/robo/ros2_ws
source /opt/ros/jazzy/setup.bash
rosdep install --from-paths src/ROS2_basic_study/ros_dd_simulation --ignore-src -r -y --rosdistro jazzy
colcon build --base-paths src/ROS2_basic_study/ros_dd_simulation --symlink-install
source install/local_setup.bash
```

빌드는 워크스페이스 루트에서 실행합니다. 아래 경로는 이 워크스페이스 기준입니다.
다른 위치에 설치했다면 `/home/robo/ros2_ws`를 실제 경로로 바꾸세요.

**새 터미널을 열 때마다 다음 두 줄을 먼저 실행합니다.**

```bash
source /opt/ros/jazzy/setup.bash
source /home/robo/ros2_ws/install/local_setup.bash
```

동일한 이름의 패키지가 있는 다른 워크스페이스를 나중에 source하면 해당 패키지가
우선 선택될 수 있습니다. 이 환경에서는 `robot_harness/harness_ws`의 설정이 선택되어
수정한 Cartographer 설정이 반영되지 않은 사례가 있었습니다.
위 명령을 실행한 뒤에는 다른 워크스페이스를 다시 source하지 마세요.

```bash
ros2 pkg prefix ros_dd_gazebo
ros2 pkg prefix ros_dd_cartographer
ros2 pkg prefix ros_dd_navigation
```

세 경로가 모두 `/home/robo/ros2_ws/install/` 아래인지 확인합니다.
오래된 `src/install` 환경은 source하지 않습니다.

## 원점과 초기 위치의 관계

| 기준 | 의미 | 설정 또는 확인 방법 |
| --- | --- | --- |
| Gazebo `world` | 시뮬레이션 공간의 고정 좌표계 | 로봇 생성 시 `x`, `y`, `z`, `yaw` 지정 |
| 로봇 `base_footprint` | 로봇과 함께 이동하는 바닥 기준 프레임 | 지도 생성 추적 기준으로 사용 |
| SLAM `map` | Cartographer가 만드는 지도 좌표계 | 새 SLAM 시작 시 로봇 위치·방향을 기준으로 초기화 |
| AMCL `initial_pose` | 저장된 지도에서 로봇의 시작 위치·방향 | `nav2_params.yaml`에서 자동 입력 |

AMCL이 별도의 지도 원점을 만드는 것은 아닙니다. 저장된 지도의 `map` 좌표계에서
로봇이 어디에 있는지 추정합니다. 거리 단위는 m, `yaw` 단위는 rad입니다.

이 문서의 절차는 로봇을 Gazebo의 `(x=0, y=0, yaw=0)`에 생성하고,
로봇 중심을 기준으로 새 지도를 시작한 뒤, 같은 위치에서 AMCL을 시작합니다.
Gazebo `world`와 SLAM `map`은 독립된 좌표계이므로 SLAM 오차와 최적화에 따른 작은
차이는 남을 수 있습니다. 모든 위치에서 두 좌표계가 정확히 일치함을 보장하지는 않습니다.

지도 YAML의 `origin`은 지도 이미지의 기준 위치입니다. 로봇의 초기 위치나
충전대 위치를 설정하려고 이 값을 임의로 `0`으로 바꾸지 마세요.

## 1. 지도 생성 전 설정

`ros_dd_cartographer/config/ros_dd_cartographer.lua`를 확인합니다.
현재 절차는 IMU를 사용하지 않는 2D SLAM 구성입니다.

```lua
map_frame = "map",
tracking_frame = "base_footprint",
published_frame = "odom",
odom_frame = "odom",
provide_odom_frame = false,
```

`tracking_frame`은 로봇 중심인 `base_footprint`를 사용합니다.
`laser_link`를 사용하면 LiDAR의 장착 위치가 시작 기준에 영향을 줍니다.
이 로봇의 LiDAR는 로봇 중심보다 앞쪽으로 0.25m 떨어져 있습니다.

설정을 수정했다면 설치본에 반영합니다.

```bash
cd /home/robo/ros2_ws
colcon build --packages-select ros_dd_cartographer --symlink-install
source install/local_setup.bash
```

기존 Navigation, Cartographer, Gazebo는 해당 실행 터미널에서 Ctrl-C로 종료합니다.
새 지도 생성 중에는 AMCL과 기존 map_server를 실행하지 않습니다.

## 2. Gazebo 원점에 로봇 생성

터미널 A에서 환경을 설정한 후 실행합니다.

```bash
ros2 launch ros_dd_gazebo ros_dd.launch.py \
  x:=0.0 y:=0.0 z:=0.05 yaw:=0.0
```

`z=0.05`는 생성 높이이며 2D 지도의 X·Y 원점과는 별개입니다.
`ros_dd.launch.py`의 기본 Y는 0.5이므로 위와 같이 **Y도 명시**합니다.
로봇이 생성된 뒤 정지한 상태를 유지합니다.

GUI 없이 실행할 때는 같은 명령에 `gz_args:="-r -s"`를 추가합니다.
GPU LiDAR는 서버 실행에서도 정상적인 렌더링 환경이 필요합니다.

## 3. 로봇을 움직이기 전에 새 SLAM 시작

터미널 B에서 환경을 설정한 후 실행합니다.
설정 경로를 명시하여 다른 워크스페이스의 설정을 읽는 것을 방지합니다.

```bash
ros2 launch ros_dd_cartographer ros_dd_cartograph.launch.py \
  use_sim_time:=true \
  cartographer_config_dir:=/home/robo/ros2_ws/install/ros_dd_cartographer/share/ros_dd_cartographer/config
```

이 명령은 저장된 지도를 불러오지 않고 새 지도를 만듭니다.
별도의 AMCL 초기 위치 설정은 이 단계에서 사용하지 않습니다.

터미널 C에서 환경을 설정한 후 시작 좌표를 확인합니다.

```bash
ros2 run tf2_ros tf2_echo map base_footprint
```

X·Y·yaw가 거의 0인지 확인합니다. 이 환경에서 확인한 시작 값은 다음과 같습니다.

```text
Translation: [-0.002, 0.010, 0.000]
Rotation: in RPY (degree) [0.000, -0.000, 0.010]
```

이는 X -2mm, Y +1cm, yaw 약 0도로 시작 기준이 거의 일치한 상태입니다.
처음에 `frame "map" ... does not exist`가 출력되더라도 이후 좌표가 계속 출력되면
초기 TF 수신 대기였을 수 있습니다. 계속 좌표가 나오지 않으면 SLAM과 센서·TF를 확인합니다.
좌표를 확인한 뒤 Ctrl-C로 조회를 종료합니다.

## 4. 지도 작성 및 저장

터미널 C에서 수동 주행을 시작합니다.

```bash
ros2 run ros_dd_teleop asdw_teleop
```

주변을 주행하며 지도를 작성합니다. 가능하면 출발 위치로 돌아와 정지한 뒤,
`map -> base_footprint`를 다시 확인해 최종 지도의 출발 좌표를 기록합니다.
지도 최적화로 출발 좌표가 달라졌다면 그 값을 이후 AMCL 초기값에 반영합니다.

다른 터미널에서 환경을 설정하고 지도를 저장합니다.

```bash
ros2 run nav2_map_server map_saver_cli -f /home/robo/map \
  --ros-args -p use_sim_time:=true
```

`/home/robo/map.yaml`과 `/home/robo/map.pgm`이 저장됩니다.
기존 지도를 보존하려면 `-f`에 다른 이름을 지정합니다.
저장이 완료되면 teleop, Cartographer와 해당 RViz, Gazebo를 종료합니다.
다음 단계에서 Gazebo를 재시작하여 로봇을 정확한 생성 위치로 되돌립니다.

## 5. AMCL 초기 위치 자동 설정

`ros_dd_navigation/config/nav2_params.yaml`의 기존 `amcl.ros__parameters` 아래에
다음 항목이 있는지 확인합니다. 같은 키를 중복 추가하지 마세요.

```yaml
amcl:
  ros__parameters:
    # 기존 AMCL 설정 유지
    set_initial_pose: true
    initial_pose:
      x: 0.0
      y: 0.0
      z: 0.0
      yaw: 0.0
```

이 값은 저장한 지도에서 출발 위치가 `(0, 0, 0)`에 가까운 경우입니다.
출발 지점에서 측정한 최종 map 좌표가 다르면 해당 X·Y·yaw(rad)를 사용합니다.
예를 들어 반시계 방향 30도는 `0.523599`, 시계 방향 30도는 `-0.523599`입니다.

## 6. 같은 출발 위치에서 저장 지도 기반 Navigation

터미널 A에서 환경을 설정하고 Gazebo를 다시 실행합니다.

```bash
ros2 launch ros_dd_gazebo ros_dd.launch.py \
  x:=0.0 y:=0.0 z:=0.05 yaw:=0.0
```

터미널 B에서 환경을 설정하고 Navigation을 실행합니다.

```bash
ros2 launch ros_dd_navigation navigation.launch.py \
  use_localization:=true \
  use_sim_time:=true \
  map:=/home/robo/map.yaml \
  params_file:=/home/robo/ros2_ws/src/ROS2_basic_study/ros_dd_simulation/ros_dd_navigation/config/nav2_params.yaml
```

저장한 지도 경로가 다르면 `map`을 변경합니다.
위 명령은 원본 파라미터 파일을 직접 읽으므로 YAML 수정 후 별도 빌드가 필요 없습니다.
실행 중 파일을 수정한 경우 Navigation을 재시작해야 적용됩니다.

**이 단계에서는 Cartographer를 실행하지 않습니다.** AMCL이 `map -> odom`을 제공합니다.
초기 위치는 자동 입력되므로 RViz의 **2D Pose Estimate**를 누를 필요가 없습니다.

다른 터미널에서 실제 적용값을 확인할 수 있습니다.

```bash
ros2 param get /amcl set_initial_pose
ros2 param get /amcl initial_pose.x
ros2 param get /amcl initial_pose.y
ros2 param get /amcl initial_pose.yaw
```

`set_initial_pose`는 `True`여야 합니다. AMCL의 `Setting pose (...)` 로그도 확인합니다.
RViz에서 LaserScan이 지도 벽과 겹치고 위치가 안정되는지 확인한 뒤
**2D Goal Pose**로 목표를 지정합니다. Nav2 시작 대기는 최신 TF의 존재를 확인하는 것으로,
위치 추정 정확도까지 보장하는 검사는 아닙니다.

초기값이 자동 적용되어도 스캔이 지도 밖으로 크게 벗어나면 목표 주행을 시작하지 말고
지도 생성 당시의 출발 위치·방향, 사용한 Cartographer 설정 경로, 월드와 지도 파일을
확인합니다. 임의의 위치에 로봇을 옮겼다면 고정된 초기값은 더 이상 맞지 않습니다.

## 기타 실행 및 점검

Cartographer로 온라인 SLAM을 계속하면서 Navigation을 실행하려면 다음을 사용합니다.
저장 지도와 AMCL을 사용하는 위 절차와는 별도 모드입니다.

```bash
ros2 launch ros_dd_navigation navigation.launch.py use_localization:=false
```

이 모드는 AMCL과 map_server를 끄고 Cartographer의 지도와 TF를 사용합니다.
`use_rviz:=false`로 Navigation의 RViz 실행을 생략할 수 있습니다.
터미널 목표 입력은 다음과 같습니다. `x y [yaw_degrees]`를 입력하며,
`cancel`은 취소, `q`는 종료입니다. 이 클라이언트의 yaw 입력 단위는 degree입니다.

```bash
ros2 run ros_dd_nav2 goto_pose --ros-args -p use_sim_time:=true
```

센서와 TF는 다음 명령으로 확인합니다.

```bash
ros2 topic echo /clock --once
ros2 topic echo /scan --once --qos-reliability best_effort
ros2 topic echo /odom --once
ros2 run tf2_ros tf2_echo odom base_footprint
ros2 run tf2_ros tf2_echo base_footprint laser_link
```

`ros_dd_gazebo/config/bridge.yaml`은 `/clock`, `/odom`, `/tf`, `/joint_states`,
`/scan`, `/imu/data`를 Gazebo에서 ROS로 전달합니다. `/cmd_vel`은 ROS에서 Gazebo로
전달하는 `geometry_msgs/msg/Twist`입니다. DiffDrive가 `odom -> base_footprint`를,
robot_state_publisher가 로봇 내부의 나머지 TF를 제공합니다.
시뮬레이션 launch의 `use_sim_time` 기본값은 `true`입니다.

Gazebo는 로컬 ground와 sun을 포함한 월드를 사용합니다.
다른 월드를 사용할 때는 `world`와 생성 대상 `world_name`을 일치시키고,
`ros_dd.world`처럼 physics, user commands, scene broadcaster, sensors(Ogre2),
IMU 시스템을 구성해야 합니다.
`gui_config:=/absolute/path/to/gui.config`로 Gazebo 카메라 설정을 바꿀 수 있습니다.

Navigation의 RViz 설정은 `rviz/navigation.rviz`입니다.
`rviz_config:=/absolute/path/to/config.rviz`로 변경할 수 있고,
`rviz_software_rendering:=true`는 RViz에만 CPU 렌더링을 적용합니다.
이는 지도와 초기 위치 불일치를 해결하는 설정은 아닙니다.

## Three-table 환경

`three_tables_mapping.launch.py`는 Gazebo와 Cartographer를 실행하고,
`three_tables_navigation.launch.py map:=/absolute/path/to/map.yaml`는 저장 지도와
AMCL, Nav2를 실행합니다. 자세한 절차는 [THREE_TABLES.md](THREE_TABLES.md)를 참고하세요.

이 환경은 기본 월드 절차와 다른 `three_tables.lua`, `three_tables_nav2.yaml`을 사용합니다.
위의 기본 설정 파일 수정이 자동으로 적용되는 것으로 가정하지 말고,
해당 환경의 출발 좌표와 추적 프레임, AMCL 초기값을 별도로 확인하세요.

## 검증 범위

이 환경에서 URDF 기반 Gazebo 실행, 원점 근처의 SLAM 시작 TF,
저장 지도 기반 AMCL 초기 위치 자동 입력을 확인했습니다.
사용자가 RViz에서 초기 위치 적용과 정상 동작을 확인했습니다.
이 기록은 모든 월드·출발 위치의 좌표 일치나 전체 경로 주행 성능을 보장하지 않습니다.

## 원점 설정에 중요한 파라미터

### 좌표계와 TF 관계

이 프로젝트의 위치 추정은 다음 TF 연결을 사용합니다.

```text
map -> odom -> base_footprint -> base_link -> laser_link
```

- `map`: 저장 지도에서의 위치를 표현하는 기준입니다.
- `odom`: 바퀴 오도메트리 기준입니다. 이동은 연속적이지만 누적 오차가 생길 수 있습니다.
- `base_footprint`: 로봇의 바닥 기준 프레임입니다. 이번 원점 정렬 절차의 로봇 기준입니다.
- `base_link`, `laser_link`: 로봇 본체와 LiDAR 장착 프레임입니다. URDF가 상대 위치를 정의합니다.

`map -> odom`은 지도 생성 중에는 Cartographer가, 저장 지도 주행 중에는 AMCL이
발행합니다. 두 노드가 동시에 같은 TF를 발행하지 않도록 실행 모드를 구분합니다.
Gazebo `world`는 이 TF 연결에 자동으로 포함되는 프레임이 아닙니다.
`world`와 `map`의 이름을 같게 바꾸거나 정적 TF를 추가하는 것만으로
지도와 실제 위치의 오차가 보정되지는 않습니다.

### Gazebo: 로봇 생성 위치

설정 위치는 `ros_dd_gazebo/launch/ros_dd.launch.py`의 실행 인자입니다.

| 인자 | 이 절차의 값 | 의미 및 주의점 |
| --- | --- | --- |
| `x` | `0.0` | Gazebo world 기준 생성 X 위치(m) |
| `y` | `0.0` | Gazebo world 기준 생성 Y 위치(m). 생략 시 기본값은 `0.5` |
| `z` | `0.05` | 생성 높이(m). AMCL의 지도상 초기 Z와 같게 만들 필요는 없음 |
| `yaw` | `0.0` | world 기준 생성 방향(rad). 0이면 로봇 정면이 world의 +X 방향 |
| `world` | 기본 `ros_dd.world` | 사용할 월드 파일. 지도 생성과 Navigation에서 같은 환경 사용 |
| `world_name` | `default` | 월드 내부 이름. 생성 대상 월드 이름과 일치해야 함 |
| `use_sim_time` | `true` | ROS 노드가 Gazebo의 `/clock`을 사용하도록 설정 |

로봇의 +X는 정면, +Y는 왼쪽, +Z는 위쪽입니다.
양의 yaw는 위에서 내려다볼 때 반시계 방향입니다.
지도 생성 전과 저장 지도 주행 전에 같은 위치·방향으로 새로 생성하는 것이 핵심입니다.
Gazebo에서 로봇을 옮겼다고 AMCL 초기값이 자동으로 갱신되지는 않습니다.

### Cartographer: 새 지도 생성의 추적 기준

설정 파일은 `ros_dd_cartographer/config/ros_dd_cartographer.lua`입니다.

| Lua 파라미터 | 현재 값 | 의미 및 주의점 |
| --- | --- | --- |
| `map_frame` | `"map"` | SLAM 결과를 표현하는 지도 프레임 이름. 원점의 숫자 좌표를 넣는 항목은 아님 |
| `tracking_frame` | `"base_footprint"` | SLAM이 추적하는 로봇 기준. 시작 시 로봇 중심을 기준으로 삼도록 지정 |
| `published_frame` | `"odom"` | 현재 구성에서 Cartographer가 map 기준 자세를 제공하는 프레임 |
| `odom_frame` | `"odom"` | Cartographer가 오도메트리 프레임을 제공하는 구성에서 사용하는 이름. 현재는 Gazebo가 해당 TF 연결을 제공 |
| `provide_odom_frame` | `false` | Gazebo가 제공하는 `odom -> base_footprint`와 중복되는 오도메트리 TF 구성을 피함 |
| `use_odometry` | `true` | 바퀴 오도메트리 정보를 SLAM에 사용. world와 map을 강제로 일치시키는 옵션은 아님 |
| `publish_frame_projected_to_2d` | `true` | 발행 자세를 바닥의 2D 이동에 맞게 투영 |
| `TRAJECTORY_BUILDER_2D.use_imu_data` | `false` | 현재 2D SLAM에서 IMU를 사용하지 않음. IMU를 켤 때는 추적 프레임 등 요구 조건을 다시 검토 |

`tracking_frame="laser_link"`와 `tracking_frame="base_footprint"`는 기준 위치가 다릅니다.
URDF의 `laser_joint`에는 LiDAR의 장착 위치와 방향이 들어 있습니다.
이 값을 화면의 오차를 없애기 위해 임의로 변경하면 센서와 로봇의 실제 기하 관계가 틀어집니다.

`map_frame`과 `tracking_frame`을 정했다고 Gazebo 생성 좌표를 자동으로 읽는 것은 아닙니다.
새 SLAM을 시작할 때 로봇을 world 원점에 정지시켜 두고 시작 TF를 확인해야 합니다.

### AMCL: 저장 지도에서의 초기 위치

설정 파일은 `ros_dd_navigation/config/nav2_params.yaml`의
`amcl -> ros__parameters` 영역입니다. 아래 항목은 모두 그 영역에 둡니다.

| YAML 파라미터 | 현재 값 | 의미 및 주의점 |
| --- | --- | --- |
| `global_frame_id` | `map` | 위치 추정의 지도 기준 프레임 |
| `odom_frame_id` | `odom` | 이동량 추정에 사용하는 오도메트리 프레임 |
| `base_frame_id` | `base_footprint` | AMCL이 위치를 추정하는 로봇 기준 프레임 |
| `set_initial_pose` | `true` | 활성화 시 아래 초기 위치를 자동 입력. 수동 2D Pose Estimate 생략에 필요 |
| `initial_pose.x` | `0.0` | map 기준 로봇 시작 X 위치(m) |
| `initial_pose.y` | `0.0` | map 기준 로봇 시작 Y 위치(m) |
| `initial_pose.z` | `0.0` | 2D 위치 추정에서 사용하는 초기 Z 값 |
| `initial_pose.yaw` | `0.0` | map 기준 로봇 시작 방향(rad) |
| `tf_broadcast` | `true` | AMCL이 `map -> odom` TF를 발행 |
| `scan_topic` | `scan` | 지도와 비교할 LiDAR 관측 토픽 |
| `use_sim_time` | `true` | 시뮬레이션의 센서·TF와 같은 시간 기준 사용 |

표의 `initial_pose.x` 등은 ROS의 파라미터 이름입니다.
YAML에는 앞 절의 예제처럼 `initial_pose:` 아래에 `x`, `y`, `z`, `yaw`를 들여써도 됩니다.
방향 변환은 `rad = degree × π / 180`이며, 30도는 약 `0.523599`, 90도는 약 `1.570796`입니다.

**AMCL 초기값은 Gazebo 좌표가 아니라 map 좌표입니다.**
이 문서의 절차에서는 두 기준을 맞춰 시작했기 때문에 같은 0 값을 사용할 수 있습니다.
다른 위치에서 시작하거나 이전 지도에 방향 오차가 있으면 그 지도에 맞는 초기값이 필요합니다.
초기값 자동 입력은 정확한 위치 추정의 완료를 뜻하지 않으므로 LaserScan 정렬도 확인합니다.

### 지도 파일과 실행 파일 선택

| 항목 | 의미 및 확인 사항 |
| --- | --- |
| 지도 YAML의 `image` | 실제 지도 이미지 경로. YAML과 해당 이미지가 함께 있어야 함 |
| 지도 YAML의 `resolution` | 픽셀 한 칸의 실제 길이(m/pixel). 원점 조정 목적으로 변경하지 않음 |
| 지도 YAML의 `origin` | 지도 이미지의 격자 원점이 map에서 갖는 `[x, y, yaw]`. 로봇 초기 위치와 별개 |
| Navigation의 `map` | 사용할 지도 YAML 경로. 생략하여 의도하지 않은 기본 지도를 읽지 않도록 명시 |
| Navigation의 `params_file` | AMCL과 Nav2가 실제 읽을 YAML 경로. 원본 경로를 명시하면 수정 파일을 직접 사용 |
| Navigation의 `use_localization` | 저장 지도 + AMCL은 `true`, Cartographer가 위치 추정 중이면 `false` |
| Cartographer의 `cartographer_config_dir` | 실제 읽을 Lua 설정 디렉터리. 워크스페이스 혼용 방지를 위해 명시 |
| Cartographer의 `configuration_basename` | 해당 디렉터리에서 읽을 Lua 파일 이름. 기본값은 `ros_dd_cartographer.lua` |

설정을 수정한 뒤에는 파일 내용뿐 아니라 실제 읽는 경로와 실행 중 파라미터를 확인합니다.
Lua 설치본을 사용하는 경우 빌드 후 Cartographer를 재시작하고,
원본 YAML을 직접 지정한 경우 Navigation을 재시작합니다.
RViz의 카메라 위치나 Grid 표시를 바꾸는 것은 지도 원점이나 AMCL 위치를 변경하지 않습니다.
