# 2륜 AGV bring-up

실행 코드는 `ros_agv/ros_agv.py`이며 실행 이름은 `ros_agv`입니다.
Arduino 펌웨어, 단독 Python 테스트, ROS 드라이버는 같은 2륜 통신 규약을 사용합니다.

## 하드웨어 설정 및 업로드

Arduino Uno 계열을 기준으로 기존 핀을 유지했습니다.

| 기능 | 핀 |
|---|---|
| 왼쪽 모터 방향(DIR) / 속도(PWM) | D12 / D10 |
| 오른쪽 모터 방향(DIR) / 속도(PWM) | D13 / D11 |
| 왼쪽 / 오른쪽 엔코더 펄스 | D2 / D3 |

모터는 DIR+PWM 방식으로 제어합니다. 방향 핀은 전진 시 HIGH, 후진 시 LOW이며,
속도는 명령의 절댓값(0~100)을 PWM(0~255)으로 변환합니다.
드라이버 모델과 입력 핀 역할을 실제 회로에서 확인해야 합니다. EN 핀만 있는 회로에는 이 설정을 그대로 적용할 수 없습니다.
모터 전원은 드라이버 사양에 맞게 별도로 공급하고 Arduino와 GND를 공유하세요.
양수 명령은 로봇 전진 기준입니다. 한쪽이 반대로 돌면 해당 `LEFT_POLARITY` 또는 `RIGHT_POLARITY`를 -1로 바꿉니다.

Arduino IDE에서 `arduino_code/ros_agv/ros_agv.ino`를 열고 실제 보드와 포트를 선택하여 업로드하세요.
ROS 실행 전에 IDE 시리얼 모니터를 닫으세요. USB 시리얼에는 디버그 문자열을 출력하지 않습니다.

엔코더는 바퀴마다 단일 펄스 입력을 사용합니다(INPUT_PULLUP, RISING).
펄스 수는 실제 인터럽트에서만 증가하며 모의 카운트는 제거했습니다.
**방향을 추정하지 않고 펄스마다 무조건 +1** 합니다. 후진이나 손으로 돌리는 경우에도 카운트가 증가합니다.
모터는 전진·후진·회전 명령을 그대로 지원하지만 엔코더는 회전량만 측정합니다.
회전당 틱 수는 감속기와 현재 RISING 계수 방식을 포함한 실제 바퀴 1회전으로 보정하세요.

## 빌드 및 실행

워크스페이스 루트에서 실행합니다(ROS Jazzy 예시).

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select ros_agv --symlink-install
source install/setup.bash
ros2 launch ros_agv bringup.launch.py serial_port:=/dev/ttyACM0
```

포트 기본값은 `/dev/ttyUSB0`, baudrate는 115200입니다. 시리얼 접근 권한이 있어야 합니다.
`serial_port`만 ROS 파라미터로 지정합니다. 나머지는 `ros_agv.py` 위쪽 상수를 수정하세요.

| 상수 | 기본값 | 의미 |
|---|---|---|
| WHEEL_SEPARATION | 0.40 | 좌우 바퀴 간격(m) |
| MAX_WHEEL_SPEED | 0.5 | 모터 명령 100에 대응하는 바퀴 선속도(m/s) |
| TICKS_PER_REVOLUTION | 1320 | 바퀴 1회전당 펄스 수 |
| CMD_TIMEOUT | 0.3 | 명령 유효 시간(s), 0.5 미만으로 설정 |
| ENCODER_TIMEOUT | 0.5 | 피드백 유효 시간(s) |

통신은 `JDamr`, ROS 처리는 `ROSAGVDriver` 클래스에 모았습니다.
`ros_agv.py` 한 파일에서 패킷 송수신까지 직접 처리하며 `protocol.py`를 사용하지 않습니다.

`cmd_vel`(geometry_msgs/Twist)의 linear.x(m/s), angular.z(rad/s)를 사용합니다.
좌우 속도를 함께 비례 제한하여 곡률을 유지합니다. PWM은 개방루프이므로 실제 속도는 부하와 배터리에 따라 달라집니다.
처음에는 바퀴를 바닥에서 띄우고 저속으로 좌우 방향과 정지를 확인하세요.

```bash
ros2 topic pub --rate 10 /cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.05}, angular: {z: 0.0}}'
```

위 발행을 Ctrl+C로 끊으면 명령 타임아웃으로 정지합니다.

### WASD 키보드 조종

드라이버를 실행한 상태에서 새 터미널을 열고 실행합니다. 추가한 노드를 사용하려면
위 빌드 명령으로 패키지를 다시 빌드하세요.

```bash
source /opt/ros/jazzy/setup.bash
source install/setup.bash
ros2 run ros_agv teleop
```

| 키 | 동작 |
|---|---|
| W / S | 전진 / 후진 |
| A / D | 제자리 좌회전 / 우회전 |
| Space 또는 다른 키 | 정지 |
| Q / Ctrl+C | 정지 요청 후 종료 |

조종 터미널에 포커스를 두고 이동 키를 누르고 계세요. 대문자도 지원합니다.
기본 속도는 0.1m/s, 회전 속도는 0.5rad/s이며 `cmd_vel`을 약 20Hz로 발행합니다.
터미널은 키를 놓는 이벤트를 제공하지 않으므로 마지막 입력 후 0.6초가 지나면 정지합니다.
키보드 자동 반복 시작이 늦으면 처음에 잠시 정지할 수 있습니다.
다른 `cmd_vel` 발행 명령은 종료한 뒤 사용하세요.

```bash
ros2 run ros_agv teleop --ros-args -p linear_speed:=0.05 -p angular_speed:=0.3 -p key_timeout:=0.6
```

피드백이 없거나 오래되면 ROS 드라이버는 정지만 보냅니다.
Arduino는 유효 모터 패킷이 500ms 동안 없으면 자체 정지합니다.
시리얼 오류가 발생하면 노드를 종료하면서 정지를 요청하고 포트를 닫습니다. 연결을 복구한 뒤 다시 실행하세요.

`joint_states`는 유효 엔코더 수신 시 약 20Hz로 발행하고, 첫 수신 위치를 0으로 설정합니다.
바퀴 각도는 32비트 카운터 차이를 부호 있는 이동량으로 해석합니다.
시뮬레이션에서는 후진 시 카운터가 감소하며, 0을 통과하는 래핑도 처리합니다.
실물 단일 채널 스케치는 방향 없는 증가 카운터이므로 실제 회전 방향을 표시하지 못합니다. 보드가 운전 중 재시작되면 ROS 노드도 재시작하세요.
### RViz 시각화

`bringup.launch.py`는 `ros_agv` 드라이버, `robot_state_publisher`, RViz를 함께 실행합니다.
teleop은 포함하지 않으므로 위의 별도 터미널 명령으로 실행하세요.
드라이버가 `joint_states`를 발행하므로 `joint_state_publisher`와 GUI는 사용하지 않습니다.
시리얼 연결 및 첫 정상 엔코더 수신 후 바퀴 TF가 표시됩니다.

`urdf/ros_agv.urdf`는 예시 차체와 바퀴 모델입니다. 바퀴 간격은 드라이버와 같은 0.40m이며,
차체 크기와 바퀴 반지름(0.075m)은 실제 측정값에 맞게 수정하세요.
RViz 설정은 `rviz/ros_agv.rviz`이며 Fixed Frame은 `base_link`입니다.
시뮬레이션에서 바퀴의 노란 표시로 전진·후진·제자리 회전 방향을 확인할 수 있습니다.
odometry와 이동 TF를 발행하지 않으므로 조종해도 RViz의 차체 위치는 고정됩니다.
PID 속도 제어는 포함하지 않습니다.

드라이버만 필요하면 기존 명령도 사용할 수 있습니다(launch와 중복 실행하지 마세요).

```bash
ros2 run ros_agv ros_agv --ros-args -p serial_port:=/dev/ttyACM0
```

## 통신 규약 (이전 예제와 호환되지 않음)

`F5 | length | command | payload | checksum`

- length: command + payload + checksum의 바이트 수.
- checksum: command와 payload의 합의 하위 8비트.
- 0x01: signed int8 왼쪽/오른쪽 명령(-100~100), length=4, 총 6바이트.
- 0x03: uint32 big-endian 왼쪽/오른쪽 누적 카운터, length=10, 총 12바이트. 시뮬레이션은 방향에 따라 증가/감소하며 ROS는 signed 모듈러 차이로 이동량을 계산합니다.

단독 Python 예제는 `in_waiting`으로 12바이트가 모였는지 확인한 뒤 헤더·길이·명령·체크섬을 검사합니다.
Arduino는 `Serial.available()`로 확인한 뒤 loop마다 한 바이트씩 저장하고, 6바이트가 모이면 검사·처리합니다.
Arduino 수신 코드는 고정 길이이며 부분 패킷 타임아웃은 생략했습니다. 시뮬레이션 스케치는 대기 중인 명령을 한 번에 처리합니다.
ROS 드라이버는 부분 수신 데이터를 보관하고 손상 패킷 뒤에서 재동기화하여 가장 최근 정상 피드백을 사용합니다.

## 모터 없이 LED로 시뮬레이션

Arduino IDE에서 `arduino_code/ros_agv_simulation/ros_agv_simulation.ino`를 열어 업로드합니다.
기존 모터 제어용 스케치 대신 선택하여 사용합니다. 별도 모터·엔코더 연결 없이 내장 LED로 동작합니다.
기존 `ros_agv.py`와 `ros_agv_pc.py`를 그대로 사용할 수 있습니다(115200 baud, 같은 패킷 형식).

- 한쪽 이상 명령이 0이 아니면 LED ON, 모두 0이면 OFF입니다.
- 가상 엔코더는 좌우 명령의 부호와 크기, 실제 경과 시간을 반영합니다. 후진은 감소하고 정지는 유지됩니다.
- 최대 바퀴 속도 0.5m/s, 반지름 0.075m, 1320 ticks/rev를 기준으로 적분하며 소수 틱을 보존합니다.
- W: 양쪽 증가, S: 양쪽 감소, A: 왼쪽 감소/오른쪽 증가, D: 왼쪽 증가/오른쪽 감소입니다.
- 펌웨어를 다시 업로드하고 ROS 패키지도 다시 빌드해야 합니다. 실물용 스케치는 변경하지 않습니다.
- 정지 중에도 누적 카운트를 50ms마다 전송합니다.
- 유효 모터 명령이 500ms 동안 없으면 자동 정지합니다.

**가상 엔코더 시험에는 반드시 `ros_agv_simulation.ino`를 업로드하세요.**
`ros_agv/ros_agv.ino`는 실물 엔코더 인터럽트 전용이므로 모터 명령만으로 카운트가 증가하지 않습니다.
ROS 드라이버는 가상 카운트를 직접 생성하지 않고 보드에서 받은 카운트로 `joint_states`를 발행합니다.

단독 Python 예제의 `LEFT_SPEED`, `RIGHT_SPEED`를 모두 `20`으로 설정하면 LED 전진을 시험할 수 있습니다.

## ROS 없이 단독 Python 테스트

ROS 노드와 시리얼 모니터를 종료한 뒤 실행합니다. pyserial이 필요합니다.

파일 위쪽의 `PORT`, `LEFT_SPEED`, `RIGHT_SPEED`, `RUN_SECONDS`만 수정하세요.
기본값은 `/dev/ttyUSB0`, 좌우 속도 0, 실행 시간 5초입니다.
저속 전진 시험은 두 속도를 각각 `20`, 실행 시간을 `3`으로 설정합니다.

```bash
python3 arduino_code/ros_agv/ros_agv_pc.py
```

속도 범위는 -100~100이며 후진(-20)에서도 엔코더 출력은 증가합니다.
`send_motor()`는 6바이트 명령을 보내고, `read_encoder()`는 12바이트 엔코더 패킷을 읽습니다.
별도 ROS 모듈이나 패키지 설치 없이 pyserial만 사용합니다.
Ctrl+C나 실행 종료 시 정지 명령을 보냅니다. 엔코더 패킷이 0.5초 이상 없으면 정지합니다.
ROS 드라이버는 수신 버퍼로 부분 패킷을 보관하고 잡음 뒤에 재동기화합니다. 시리얼 포트는 독점으로 엽니다.

## 검증

`test_ros_agv.py`는 현재 단일 파일 드라이버를 검사합니다.
`test_simulation_firmware.py`는 실제 시뮬레이션 스케치를 Arduino API 대역과 함께 컴파일하여 명령·카운트·워치독을 검사합니다(g++ 필요).
`test_protocol.py`는 삭제된 이전 모듈을 참조하므로 현재 검증 대상에서 제외합니다.

```bash
cd ros_agv
python3 -m pytest test/test_ros_agv.py test/test_simulation_firmware.py
```

실물의 모터 드라이버, 방향, 엔코더 해상도 및 정지 동작은 해당 하드웨어에서 확인해야 합니다.
