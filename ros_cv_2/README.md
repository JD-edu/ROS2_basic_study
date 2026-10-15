# 두 카메라 독립 저지연 전송

기존 ros_cv의 현재 캡처/JPEG 전송 코드를 복제한 두 번째 패키지입니다.
640×480, JPEG 품질 50, BEST_EFFORT / KEEP_LAST / depth=1,
V4L2 버퍼 1 및 전용 캡처 스레드를 유지합니다.
두 송신기는 별도 프로세스로 동작합니다. 실제 지연과 FPS는 USB 대역폭,
카메라 드라이버, CPU, 네트워크에 따라 달라집니다.

| 패키지 | 송신 노드 | 기본 장치 | 송수신 토픽 |
| --- | --- | --- | --- |
| ros_cv | /cam_pub | /dev/video0 | /camera/image/compressed |
| ros_cv_2 | /cam_pub_2 | /dev/video2 | /camera2/image/compressed |

## 빌드 (송신 장치와 수신 PC)

두 패키지를 각 장치의 워크스페이스 src에 배치한 뒤 실행합니다.

```bash
cd ~/ros2_ws
source /opt/ros/jazzy/setup.bash
colcon build --packages-select ros_cv ros_cv_2 --symlink-install
source install/setup.bash
```

## 송신 장치: 동시에 시작

```bash
ros2 launch ros_cv_2 dual_cameras.launch.py camera2_device:=/dev/video2
```

장치 번호는 실제 환경에서 확인해야 합니다. 하나의 USB 카메라가 여러
/dev/video* 장치를 만들 수 있으므로 두 번째 카메라가 /dev/video1이라는
뜻은 아닙니다. `v4l2-ctl --list-devices` 또는 `ls -l /dev/v4l/by-id/`
명령으로 확인합니다. 기본 /dev/video2 역시 실제 두 번째 카메라의 캡처
장치인지 확인하세요. camera2_device에는 /dev/v4l/by-id/... 경로도 가능합니다.
첫 번째 카메라는 기존 코드에 따라 /dev/video0을 사용합니다.

개별 실행하려면 서로 다른 터미널에서 실행합니다 (launch와 중복 실행 금지).

```bash
ros2 run ros_cv cam_pub
ros2 run ros_cv_2 cam_pub --ros-args -p camera_device:=/dev/video2
```

## 수신 PC: 터미널 두 개에서 실행

각 터미널에서 install/setup.bash를 source하고 다음 명령을 하나씩 실행합니다.
기존 ros_cv 수신기의 video_frames를 첫 카메라 송신 토픽으로 remap합니다.

```bash
ros2 run ros_cv cam_sub --ros-args -r video_frames:=/camera/image/compressed
ros2 run ros_cv_2 cam_sub
```

수신 창은 camera, camera2이며 수신 노드는 image_subscriber,
image_subscriber_2입니다. PC에는 OpenCV GUI를 표시할 데스크톱 환경이 필요합니다.
송신 장치와 PC는 ROS_DOMAIN_ID를 동일하게 설정하고 서로 DDS 통신이 가능한
네트워크에 연결합니다. 두 번째 송수신 토픽을 바꾸려면 양쪽에 같은
`--ros-args -r camera2/image/compressed:=/원하는/토픽`을 적용합니다.

새 수신기는 NumPy와 OpenCV로 JPEG를 직접 디코딩합니다. 기존 ros_cv
수신기는 cv_bridge를 사용하므로 PC의 NumPy/cv_bridge 버전 호환이 필요합니다.

## RGB 2대 + Astra depth 1대 동시 시작

`rgbd_cameras.launch.py`는 Astra의 color/IR/point cloud를 끄고 다음 세 영상만
퍼블리시합니다.

| 영상 | 토픽 | 타입 |
| --- | --- | --- |
| RGB 카메라 1 | `/camera1/image/compressed` | `sensor_msgs/msg/CompressedImage` |
| RGB 카메라 2 | `/camera2/image/compressed` | `sensor_msgs/msg/CompressedImage` |
| Astra depth | `/depth_camera/depth/image_raw` | `sensor_msgs/msg/Image` |

depth 카메라 워크스페이스와 이 워크스페이스를 순서대로 source하는 실행 스크립트를
사용합니다.

```bash
cd ~/ros2_ws
./run_rgbd_cameras.bash
```

카메라 장치가 기본값(`/dev/video0`, `/dev/video2`)과 다르면 런치 인자로 바꿉니다.

```bash
./run_rgbd_cameras.bash \
  camera1_device:=/dev/v4l/by-id/첫번째카메라-video-index0 \
  camera2_device:=/dev/v4l/by-id/두번째카메라-video-index0
```

확인은 다른 터미널에서 두 워크스페이스를 source한 뒤 실행합니다.

```bash
ros2 topic hz /camera1/image/compressed
ros2 topic hz /camera2/image/compressed
ros2 topic hz /depth_camera/depth/image_raw
```
