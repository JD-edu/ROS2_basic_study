#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// 50ms마다 콜백 호출 (20Hz 발행)
using namespace std::chrono_literals;

class WebcamPublisher : public rclcpp::Node
{
public:
    WebcamPublisher()
    : Node("webcam_publisher"), count_(0)
    {
        // 1. 웹캠 열기: 0은 보통 첫 번째 카메라 장치를 의미합니다.
        cap_.open(0);
        if (!cap_.isOpened()) {
            RCLCPP_ERROR(this->get_logger(), "Error: Could not open camera.");
            // 치명적인 오류 발생 시 ROS 노드 종료
            rclcpp::shutdown(); 
            return;
        }

        // 2. 발행자 생성: sensor_msgs::msg::Image 타입으로 "camera/image" 토픽에 발행
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("camera/image", 10);

        // 3. 타이머 생성: 50ms마다 timer_callback 함수 호출
        timer_ = this->create_wall_timer(
            50ms,
            std::bind(&WebcamPublisher::timer_callback, this)
        );

        RCLCPP_INFO(this->get_logger(), "Webcam Publisher Node started.");
    }

private:
    void timer_callback()
    {
        cv::Mat frame;
        
        // 1. 웹캠에서 새 프레임 캡처
        cap_ >> frame;

        if (frame.empty()) {
            RCLCPP_WARN(this->get_logger(), "Warning: Captured empty frame.");
            return;
        }

        // 2. OpenCV Mat을 ROS Image 메시지로 변환
        // cv_bridge::CvImage 객체를 생성하여 변환을 준비합니다.
        // - frame.header: 나중에 메시지에 타임스탬프를 설정하기 위해 사용
        // - "bgr8": OpenCV의 일반적인 색상 인코딩 (Blue, Green, Red, 8bit)
        // - frame: 캡처된 OpenCV Mat 데이터
        std_msgs::msg::Header header;
        header.stamp = this->now(); // 현재 ROS 시간으로 타임스탬프 설정

        // CvImage 객체를 만들고 toImageMsg()로 변환
        auto msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
        
        // 3. 메시지 발행
        publisher_->publish(*msg);

        RCLCPP_INFO(this->get_logger(), "Image frame %zu published.", count_++);
    }

    // 멤버 변수 선언
    cv::VideoCapture cap_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<WebcamPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}