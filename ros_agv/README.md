# 2륜 AGV bring-up

`ros_agv_2.py` 기반 드라이버입니다. `ros_agv`와 `ros_agv_2` 실행 이름은 같은 새 드라이버를 실행합니다.
이전 `ros_agv.py` 및 `arduino_code/ros_agv/ros_agv_pc.py`는 과거 예제이며 새 펌웨어와 호환되지 않습니다.
새 Python 코드와 새 펌웨어를 반드시 함께 사용하세요.

## 하드웨어 설정 및 업로드

Arduino Uno 계열을 기준으로 기존 핀을 유지했습니다.

| 기능 | 핀 |
|---|---|
| 왼쪽 모터 입력 1 / 입력 2(PWM) | D12 / D10 |
| 오른쪽 모터 입력 1 / 입력 2(PWM) | D13 / D11 |
| 왼쪽 / 오른쪽 엔코더 펄스 | D2 / D3 |

원본 코드에 L9110이라고 기재되어 있어 `L9110_MODE = true`가 기본입니다.
실제 보드가 DIR+PWM 인터페이스라면 `.ino`에서 `false`로 바꾸세요.
드라이버 모델과 입력 핀 역할을 실제 회로에서 확인해야 합니다. EN 핀만 있는 회로에는 이 설정을 그대로 적용할 수 없습니다.
모터 전원은 드라이버 사양에 맞게 별도로 공급하고 Arduino와 GND를 공유하세요.
양수 명령은 로봇 전진 기준입니다. 한쪽이 반대로 돌면 해당 `LEFT_POLARITY` 또는 `RIGHT_POLARITY`를 -1로 바꿉니다.

Arduino IDE에서 `arduino_code/ros_agv/ros_agv.ino`를 열고 실제 보드와 포트를 선택하여 업로드하세요.
ROS 실행 전에 IDE 시리얼 모니터를 닫으세요. USB 시리얼에는 디버그 문자열을 출력하지 않습니다.

엔코더는 바퀴마다 단일 펄스 입력을 사용합니다(INPUT_PULLUP, RISING).
펄스 수는 실제 인터럽트에서만 증가하며 모의 카운트는 제거했습니다.
**방향은 모터 명령에서 추정**하므로 외력 이동, 정지 후 관성, 실제 역회전은 정확히 측정할 수 없습니다.
정확한 방향 측정이 필요하면 바퀴마다 A/B 채널을 연결하고 쿼드러처 해독으로 확장해야 합니다.
회전당 틱 수는 감속기와 현재 RISING 계수 방식을 포함한 실제 바퀴 1회전으로 보정하세요.

## 빌드 및 실행

워크스페이스 루트에서 실행합니다(ROS Jazzy 예시).

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select ros_agv --symlink-install
source install/setup.bash
ros2 run ros_agv ros_agv --ros-args -p serial_port:=/dev/ttyACM0
```

포트 기본값은 `/dev/ttyUSB0`, baudrate는 115200입니다. 시리얼 접근 권한이 있어야 합니다.
주요 시작 파라미터:

| 파라미터 | 기본값 | 의미 |
|---|---|---|
| wheel_separation | 0.40 | 좌우 바퀴 간격(m) |
| max_wheel_speed | 0.5 | 모터 명령 100에 대응하는 바퀴 선속도(m/s) |
| encoder_ticks_per_revolution | 1320.0 | 바퀴 1회전당 펄스 수 |
| cmd_vel_timeout | 0.3 | 명령 유효 시간(s), 0.5 미만 |
| encoder_timeout | 0.5 | 피드백 유효 시간(s) |
| startup_delay | 2.0 | 포트 연결 후 Arduino 재시작 대기(s) |
| left_joint_name / right_joint_name | left_wheel_joint / right_wheel_joint | URDF와 맞출 관절 이름 |

`cmd_vel`(geometry_msgs/Twist)의 linear.x(m/s), angular.z(rad/s)를 사용합니다.
좌우 속도를 함께 비례 제한하여 곡률을 유지합니다. PWM은 개방루프이므로 실제 속도는 부하와 배터리에 따라 달라집니다.
처음에는 바퀴를 바닥에서 띄우고 저속으로 좌우 방향과 정지를 확인하세요.

```bash
ros2 topic pub --rate 10 /cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.05}, angular: {z: 0.0}}'
```

위 발행을 Ctrl+C로 끊으면 명령 타임아웃으로 정지합니다.
피드백이 없거나 오래되면 ROS 드라이버는 정지만 보냅니다.
Arduino는 유효 모터 패킷이 500ms 동안 없으면 자체 정지합니다.
시리얼 오류는 정지 요청 후 드라이버를 오류 상태로 고정하므로 연결을 복구하고 노드를 재시작하세요.

`joint_states`는 유효 엔코더 수신 시 약 20Hz로 발행하고, 첫 수신 위치를 0으로 설정합니다.
32비트 카운터 래핑을 처리합니다. 보드가 운전 중 재시작되면 ROS 노드도 재시작하세요.
현재 패키지는 바퀴 상태까지 제공하며 RViz/URDF, odometry, 이동 TF, PID 속도 제어는 포함하지 않습니다.

## 통신 규약 (이전 예제와 호환되지 않음)

`F5 | length | command | payload | checksum`

- length: command + payload + checksum의 바이트 수.
- checksum: command와 payload의 합의 하위 8비트.
- 0x01: signed int8 왼쪽/오른쪽 명령(-100~100), length=4, 총 6바이트.
- 0x03: signed int32 big-endian 왼쪽/오른쪽 누적 펄스, length=10, 총 12바이트.

Python 파서는 분할/연속 패킷을 버퍼링하고 길이 및 체크섬 오류에서 재동기화합니다.
Arduino는 부분 패킷을 다음 loop까지 보관하고 50ms가 지나면 버립니다.

## 검증

```bash
cd ros_agv
python3 -m pytest test/test_protocol.py
```

실물의 모터 드라이버, 방향, 엔코더 해상도 및 정지 동작은 해당 하드웨어에서 확인해야 합니다.
