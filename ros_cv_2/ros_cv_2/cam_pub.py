import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
from sensor_msgs.msg import CompressedImage
import cv2
import threading

class ExtremeLowLatencyPub(Node):
    def __init__(self):
        super().__init__('cam_pub_2')
        self.declare_parameter('camera_device', '/dev/video2')
        camera_device = self.get_parameter('camera_device').value
        
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        self.publisher = self.create_publisher(
            CompressedImage, 
            'camera2/image/compressed', 
            qos_profile
        )

        # V4L2 백엔드 사용
        self.cap = cv2.VideoCapture(camera_device, cv2.CAP_V4L2)
        if not self.cap.isOpened():
            self.cap.release()
            self.destroy_node()
            raise RuntimeError(f"카메라를 열 수 없습니다: {camera_device}")
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
        self.cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)

        # [핵심] 자동 노출 끄고 셔터 지연 방지 (필요 시 환경에 맞게 수치 조절)
        # 1: 수동 모드, 3: 자동 모드 (V4L2 기준)
        self.cap.set(cv2.CAP_PROP_AUTO_EXPOSURE, 1)
        self.cap.set(cv2.CAP_PROP_EXPOSURE, 150)  # 수치가 낮을수록 잔상/지연 감소, 영상은 어두워짐

        # 인코딩 속도 극대화 (품질 50, 압축 시간 최소화)
        self.encode_param = [
            int(cv2.IMWRITE_JPEG_QUALITY), 50,
            int(cv2.IMWRITE_JPEG_OPTIMIZE), 0  # 압축 최적화 연산 끔 (CPU 딜레이 방지)
        ]

        self.running = True
        # 타이머 대신 전용 캡처 스레드 가동
        self.worker_thread = threading.Thread(target=self.capture_loop, daemon=True)
        self.worker_thread.start()
        self.get_logger().info("극한 저지연 동기화 모드 시작")

    def capture_loop(self):
        while self.running and self.cap.isOpened():
            # grab()으로 이전 큐를 털어내고 최신 프레임만 retrieve
            self.cap.grab()
            ret, frame = self.cap.retrieve()
            if not ret:
                continue

            # 빠른 JPEG 인코딩
            success, buffer = cv2.imencode('.jpg', frame, self.encode_param)
            if not success:
                continue

            msg = CompressedImage()
            msg.header.stamp = self.get_clock().now().to_msg()
            msg.header.frame_id = "camera2_optical_frame"
            msg.format = "jpeg"
            msg.data = buffer.tobytes()

            self.publisher.publish(msg)

    def destroy_node(self):
        self.running = False
        if hasattr(self, "worker_thread"):
            self.worker_thread.join()
        self.cap.release()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = None
    try:
        node = ExtremeLowLatencyPub()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if node is not None:
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()