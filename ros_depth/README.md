# 카메라 수신 노드

기존 `ros_cv`, `ros_cv_2`의 JPEG 수신 노드와 16UC1 depth 수신 노드를
동시에 실행합니다. Depth 값의 단위는 mm이며, 화면 중앙의 거리도 표시합니다.

```bash
cd ~/ros2_ws
source /opt/ros/$ROS_DISTRO/setup.bash
colcon build --packages-select ros_cv ros_cv_2 ros_depth --symlink-install
source install/setup.bash
ros2 launch ros_depth camera_receivers.launch.py
```

개별 depth 수신 노드만 실행할 수도 있습니다.

```bash
ros2 run ros_depth depth_sub
```

기본 depth 표시 범위는 0~5000 mm입니다. 필요하면 실행 시 변경합니다.

```bash
ros2 run ros_depth depth_sub --ros-args -p max_depth_mm:=10000
```

종료는 영상 창에서 `q`를 누르거나 터미널에서 `Ctrl+C`를 누릅니다.
