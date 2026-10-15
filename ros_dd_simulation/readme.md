# goto_pose 반복 목표 입력

`ros_dd_nav2`의 `goto_pose`를 실행하면 터미널에서 목표 좌표를 계속 입력할 수 있습니다.
한 목표의 이동이 성공·실패·취소로 끝나면 다음 목표를 입력받습니다.
이동 중 입력한 새 목표는 경고 후 무시합니다. 완료 메시지를 확인하고 다시 입력하세요.
이동 중에도 종료 명령을 입력할 수 있습니다.

## 1. 빌드

```bash
cd /home/robo/ros2_ws
source /opt/ros/humble/setup.bash
colcon build --packages-select ros_dd_nav2
source install/setup.bash
```

ROS 배포판이 Humble이 아니면 해당 배포판의 `setup.bash`를 사용하세요.
새 터미널에서도 ROS 환경과 워크스페이스의 `install/setup.bash`를 불러오세요.

## 2. 시뮬레이션 및 Nav2 준비

먼저 Gazebo, 위치 추정(AMCL 또는 Cartographer), Nav2를 실행해야 합니다.
기존 실행 절차는 [SLAM 실행 안내](how_to_run_robot_SLAM.md)를 참고하세요.
AMCL을 사용한다면 RViz의 **2D Pose Estimate**로 초기 위치를 설정하세요.
이 프로그램은 초기 위치를 자동 설정하지 않습니다.

## 3. 목표 입력 프로그램 실행

Gazebo 환경(AMCL과 Cartographer 모두 동일):

```bash
ros2 run ros_dd_nav2 goto_pose --ros-args -p use_sim_time:=true
```

`navigate_to_pose` Action 서버가 검색될 때까지 기다린 뒤 입력을 받습니다.
서버 검색은 위치 추정이나 지도 준비 완료를 보장하지 않으므로 먼저 Nav2와 위치 추정을 준비하세요.
기존 `localizer` 옵션은 더 이상 사용하지 않습니다.
실제 로봇에서 시뮬레이션 시계를 사용하지 않는다면 `use_sim_time:=true` 옵션을 생략하세요.

## 4. 입력 형식과 예시

공백으로 구분한 `x y yaw` 세 숫자를 입력하고 Enter를 누릅니다.

- `x`, `y`: `map` 좌표계의 목표 위치, 단위는 미터(m)
- `yaw`: 목표 방향, 단위는 도(°). 0은 +X 방향, 90은 +Y 방향이며 양수는 반시계 방향입니다.

```text
목표 입력> 2.0 3.0 90
[INFO] 목표 요청: x=2.0, y=3.0, yaw=90.0도
...
[SUCCESS] 목표 지점에 성공적으로 도달했습니다!
목표 입력> 0 0 0
...
목표 입력> -1.5 2.0 -90
...
목표 입력> q
```

이동 중에는 남은 거리를 주기적으로 표시합니다. 잘못된 입력(숫자 개수 오류,
문자, NaN, 무한대)은 목표로 전송하지 않고 다시 입력받습니다. 빈 줄은 무시합니다.

`q`, `quit`, `exit`, EOF(Ctrl+D) 또는 Ctrl+C로 종료할 수 있습니다.
이동 중 종료하면 비동기 취소를 요청하고 최종 결과를 기다립니다.
목표 수락 대기 중 종료해도 수락 응답을 받은 뒤 취소합니다.
5초 안에 결과가 오지 않으면 경고 후 프로그램을 종료하므로 로봇 정지 여부를 확인하세요.
Ctrl+C를 다시 누르면 대기를 중단하고 종료합니다.
프로그램 종료 시 Nav2 스택은 계속 실행되므로 프로그램을 다시 실행할 수 있습니다.

## 5. Action 콜백 구조

`BasicNavigator`의 `isTaskComplete()` 반복 호출을 제거하고,
`ActionClient(NavigateToPose, 'navigate_to_pose')`를 직접 사용합니다.

| 함수 | 역할 |
| --- | --- |
| `process_commands()` | 입력 검증 후 `send_goal_async()`로 목표 전송 |
| `on_goal_response()` | 목표 수락·거부 응답 처리, `get_result_async()` 결과 콜백 등록 |
| `on_feedback()` | 피드백 수신 시 남은 거리 표시(최대 약 1초에 한 번) |
| `on_result()` | 성공·취소·실패 결과 처리, 다음 목표 허용 |
| `cancel_goal()` / `on_cancel_response()` | 비동기 취소 요청과 응답 처리 |

메인 스레드는 `rclpy.spin()`으로 ROS 이벤트를 처리합니다.
별도 입력 스레드는 `input()`으로 받은 문자열을 큐에 넣고 GuardCondition을 깨웁니다.
`process_commands()`는 Executor에서 실행되며 Action 상태 변경도 이 스레드에서 처리합니다.
입력 큐 확인용 타이머나 Action 완료 여부를 확인하는 폴링 루프는 없습니다.
시작 시 서버 검색에만 `wait_for_server()`를 사용하며, 종료 시에는 5초 제한 타이머를 사용합니다.
