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
