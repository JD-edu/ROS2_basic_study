import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
from sensor_msgs.msg import CompressedImage
import cv2
import numpy as np
import threading
import time

class ExtremeLowLatencySub(Node):
    def __init__(self):
        super().__init__('cam_sub')
        
        # 송신단과 동일한 초저지연 QoS 프로파일
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,  # 재전송 대기 없이 즉시 폐기
            history=HistoryPolicy.KEEP_LAST,
            depth=1                                     # 버퍼 크기 1
        )
        
        self.subscription = self.create_subscription(
            CompressedImage,
            'camera/image/compressed',
            self.listener_callback,
            qos_profile
        )
        
        # 최신 프레임 저장소 및 락(Lock)
        self.latest_frame = None
        self.latency_ms = 0.0
        self.lock = threading.Lock()
        
        self.get_logger().info("초저지연 서브스크라이버 수신 대기 시작")

    def listener_callback(self, msg):
        """ROS2 메시지 수신 전용 콜백 (블로킹 연산 절대 금지)"""
        # 1. 지연 시간(ms) 계산 (송신단과 PC의 시계가 동기화되어 있어야 정확함)
        recv_time_ns = self.get_clock().now().nanoseconds
        send_time_ns = msg.header.stamp.sec * 1_000_000_000 + msg.header.stamp.nanosec
        diff_ms = (recv_time_ns - send_time_ns) / 1_000_000.0

        # 2. 빠른 JPEG 디코딩
        np_arr = np.frombuffer(msg.data, np.uint8)
        frame = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)

        if frame is not None:
            # 3. 최신 프레임만 빠르게 덮어쓰고 콜백 즉시 종료 (imshow 금지)
            with self.lock:
                self.latest_frame = frame
                self.latency_ms = diff_ms


def main(args=None):
    rclpy.init(args=args)
    node = ExtremeLowLatencySub()

    # ROS2 통신 처리를 별도 백그라운드 스레드에서 단독 실행
    executor_thread = threading.Thread(target=rclpy.spin, args=(node,), daemon=True)
    executor_thread.start()

    print("[실행 중] 'q' 키를 누르면 종료됩니다.")

    try:
        # 메인 스레드는 화면 렌더링(cv2.imshow)만 전담
        while rclpy.ok():
            frame_to_show = None
            latency = 0.0

            # 최신 프레임 1장만 복사해오기
            with node.lock:
                if node.latest_frame is not None:
                    frame_to_show = node.latest_frame.copy()
                    latency = node.latency_ms

            if frame_to_show is not None:
                # 화면 좌측 상단에 지연 시간(Latency) 텍스트 출력
                text = f"Latency: {latency:.1f} ms"
                cv2.putText(frame_to_show, text, (20, 40), 
                            cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2, cv2.LINE_AA)
                
                cv2.imshow("Extreme Low Latency Stream", frame_to_show)

            # 키 입력 대기 (1ms)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

            # 렌더링 루프의 과도한 CPU 점유 방지 (약 120fps 한도)
            time.sleep(0.005)

    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        cv2.destroyAllWindows()
        rclpy.shutdown()
        executor_thread.join(timeout=1.0)

if __name__ == '__main__':
    main()