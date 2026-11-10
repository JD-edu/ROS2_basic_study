# DIY 가상 라이다

실제 라이다 없이 아두이노가 가상 거리값을 계산하고 USB 시리얼로 PC에 전송합니다.
ROS2 브리지는 이 값을 `sensor_msgs/msg/LaserScan`으로 발행합니다.
Tkinter 뷰어는 ROS2 토픽 또는 시리얼 데이터를 받아 점으로 표시합니다.

```text
Arduino (가상 센서 계산) ─ USB 115200 baud ─ lidar_bridge ─ /scan ─ lidar_viewer
```

## 준비 및 빌드

Arduino IDE에서 `arduino/lidar_simulator/lidar_simulator.ino`를 열고 보드와 포트를
선택하여 업로드합니다. 별도의 센서나 Arduino 라이브러리는 필요 없습니다.
시뮬레이션은 센서 중심의 가로·세로 6 m 방과 움직이는 반지름 0.4 m 원형 장애물입니다.
360개 방향을 약 5 Hz로 전송합니다. Uno에서도 전체 스캔 배열을 저장하지 않습니다.

```bash
sudo apt install python3-serial python3-tk
source /opt/ros/jazzy/setup.bash
cd ~/ros2_ws
colcon build --packages-select diy_lidar --symlink-install
source install/setup.bash
```

## ROS2로 수신하여 시각화

터미널 1 (보드에 따라 `/dev/ttyUSB0` 등으로 포트를 변경):

```bash
ros2 run diy_lidar lidar_bridge --ros-args -p port:=/dev/ttyACM0
```

터미널 2 (ROS2 및 워크스페이스 setup.bash를 먼저 source):

```bash
ros2 run diy_lidar lidar_viewer --mode ros
```

확인: `ros2 topic echo /scan --qos-reliability best_effort`

## RViz와 브리지를 한 번에 실행

패키지를 다시 빌드하고 워크스페이스를 source한 후 실행합니다.
아두이노에 위 스케치를 업로드하고 연결해 두세요.

```bash
ros2 launch diy_lidar lidar.launch.py port:=/dev/ttyACM0
```

RViz에 1 m 격자, 센서 좌표축, `/scan`의 초록색 점이 위에서 본 모습으로 표시됩니다.
빨간 축은 전방(+X), 초록 축은 좌측(+Y)입니다.
Fixed Frame은 `laser_frame`이며 센서 자체 좌표를 사용하므로 별도 TF가 필요 없습니다.
LaserScan 구독 QoS는 브리지와 호환되는 Best Effort로 설정했습니다.

```bash
# 이미 브리지가 실행 중이면 RViz만 실행
ros2 launch diy_lidar lidar.launch.py use_bridge:=false

# 화면 없이 브리지만 실행
ros2 launch diy_lidar lidar.launch.py use_rviz:=false port:=/dev/ttyUSB0

# 프레임 이름 변경 (브리지와 RViz에 함께 적용)
ros2 launch diy_lidar lidar.launch.py frame_id:=my_laser
```

추가 launch 인자는 `baud`(기본 115200)입니다. 같은 포트를 사용하는 기존 브리지나
시리얼 직접 수신 뷰어를 종료한 뒤 실행하세요. Tkinter의 ROS 모드는 함께 사용할 수 있습니다.

뷰어는 센서를 가운데 주황색 삼각형으로, 거리값을 초록색 점으로 표시합니다.
위쪽이 전방(+X), 왼쪽이 좌측(+Y)이며 원형 눈금은 1 m 간격입니다.
1초 이상 데이터가 없으면 `STALE`로 표시합니다.
`--max-range 8`로 표시 범위를 변경할 수 있습니다.

## ROS2 없이 아두이노 직접 테스트

시리얼 포트는 한 프로그램만 열 수 있습니다. Arduino 시리얼 모니터와 브리지를
종료한 뒤 실행하세요.

```bash
ros2 run diy_lidar lidar_viewer --mode serial --port /dev/ttyACM0
```

빌드와 ROS2 없이도 패키지 디렉터리에서 실행할 수 있습니다.

```bash
cd ~/ros2_ws/src/ROS2_basic_study/diy_lidar
python3 -m diy_lidar.lidar_viewer --mode serial --port /dev/ttyACM0
```

## 아두이노 없이 화면 테스트

```bash
python3 -m diy_lidar.lidar_viewer --mode demo
```

데모는 PC에서 같은 가상 공간을 계산합니다. USB 전송과 ROS2 브리지는 테스트하지 않습니다.
Tkinter 창을 띄우려면 데스크톱 화면 환경이 필요합니다.

## 통신 규약 및 ROS2 설정

각 줄: `SCAN,200,d0,d1,...,d359` + 개행. 두 번째 필드는 스캔 주기(ms),
거리 필드는 정수 mm입니다. 각도는 0도 전방부터 반시계 방향으로 1도 간격입니다.
불완전하거나 잘못된 프레임은 버리고, 0.05~8 m 밖의 값은 무한대로 처리합니다.
360방향은 한 시점에 계산된 가상 스냅샷이므로 `time_increment`는 0입니다.
ROS 타임스탬프는 PC 수신 시각입니다. TF는 발행하지 않습니다.

브리지 파라미터: `port`, `baud` (115200), `frame_id` (`laser_frame`), `topic` (`/scan`).
뷰어 토픽은 `--topic /scan`으로 설정합니다. 센서 데이터 QoS를 사용합니다.
USB가 끊기면 프로그램을 종료하고 다시 실행하세요. 포트 권한 오류가 나면
`sudo usermod -aG dialout "$USER"` 후 로그아웃하고 다시 로그인하세요.
