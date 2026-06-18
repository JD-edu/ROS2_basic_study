#include <rclcpp/rclcpp.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp> // cv::imshow, cv::waitKey를 위해 필요
#include <algorithm> // for std::remove

// 사용자 정의 메시지 헤더 포함
#include "cv_msg/msg/msg_center.hpp"

using namespace std::chrono_literals;

class ColorDetectorNode : public rclcpp::Node
{
public:
    ColorDetectorNode() : Node("color_detector_node")
    {
        // 1. 파라미터 선언 및 가져오기
        this->declare_parameter<int>("camera_index", 0); // 웹캠 장치 인덱스 (보통 0)
        int camera_index = this->get_parameter("camera_index").as_int();
        
        // 2. 발행자 생성: 사용자 정의 메시지 타입 발행
        publisher_ = this->create_publisher<cv_msg::msg::MsgCenter>("red_center", 10);
        
        // 3. 카메라 초기화 (OpenCV VideoCapture)
        cap_.open(camera_index);
        
        if (!cap_.isOpened())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open camera device at index %d.", camera_index);
            throw std::runtime_error("Camera failed to open."); 
        }

        // 4. 타이머 설정: 30ms (약 33 FPS) 주기로 이미지 처리 함수 호출
        timer_ = this->create_wall_timer(
            33ms, std::bind(&ColorDetectorNode::process_frame_and_publish, this));
            
        RCLCPP_INFO(this->get_logger(), "Color Detector Node started. Reading from camera %d and publishing 'red_center'.", camera_index);
    
        // OpenCV 창 생성 (선택 사항: 창이 미리 생성되도록)
        cv::namedWindow("Original Frame", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Red Mask", cv::WINDOW_AUTOSIZE);
    }

    ~ColorDetectorNode()
    {
        if (cap_.isOpened())
        {
            cap_.release();
            RCLCPP_INFO(this->get_logger(), "Camera device released.");
        }
        // OpenCV 창 파괴
        cv::destroyAllWindows(); 
    }

private:
    void process_frame_and_publish()
    {
        cv::Mat frame;
        
        // 1. 카메라에서 새 프레임 읽기
        cap_ >> frame;

        if (frame.empty()) 
        {
            RCLCPP_WARN(this->get_logger(), "Failed to read a frame from the camera.");
            return;
        }

        // --- 2. 빨간색 영역 검출 및 중심점 계산 (OpenCV 처리) ---
        cv::Mat hsv_frame, mask1, mask2, red_mask;
        
        // BGR을 HSV로 변환
        cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

        // 빨간색 검출을 위한 두 영역의 마스크 생성
        // Lower Red Range
        cv::inRange(hsv_frame, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), mask1);
        // Upper Red Range
        cv::inRange(hsv_frame, cv::Scalar(170, 100, 100), cv::Scalar(180, 255, 255), mask2);
        
        cv::addWeighted(mask1, 1.0, mask2, 1.0, 0.0, red_mask);

        // Contours 찾기
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(red_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // 가장 큰 Contours 찾기
        double max_area = 0;
        int max_contour_idx = -1;
        for (size_t i = 0; i < contours.size(); i++)
        {
            double area = cv::contourArea(contours[i]);
            if (area > max_area)
            {
                max_area = area;
                max_contour_idx = i;
            }
        }

        // --- 3. 중심점 계산 및 메시지 발행 ---
        auto center_msg = cv_msg::msg::MsgCenter();
        center_msg.x = -1; // 기본값 (발견되지 않음)
        center_msg.y = -1;

        if (max_contour_idx >= 0 && max_area > 100) // 최소 영역 크기 필터링
        {
            cv::Moments m = cv::moments(contours[max_contour_idx]);
            
            if (m.m00 > 0)
            {
                // 중심점 좌표 계산: (m10/m00, m01/m00)
                int center_x = static_cast<int>(m.m10 / m.m00);
                int center_y = static_cast<int>(m.m01 / m.m00);

                // 사용자 정의 메시지에 값 할당 (int64로 변환)
                center_msg.x = static_cast<int64_t>(center_x);
                center_msg.y = static_cast<int64_t>(center_y);
                
                RCLCPP_INFO(this->get_logger(), "Detected Red Center: (%ld, %ld)", center_msg.x, center_msg.y);

                // 디버깅용: 원본 프레임에 중심점 표시 (빨간색 원)
                cv::circle(frame, cv::Point(center_x, center_y), 5, cv::Scalar(0, 0, 255), -1);
                // 가장 큰 컨투어 그리기 (녹색)
                cv::drawContours(frame, contours, max_contour_idx, cv::Scalar(0, 255, 0), 2);
            }
        }

        // 메시지 발행
        publisher_->publish(center_msg);

        // --- 4. cv::imshow로 영상 출력 ---
        cv::imshow("Original Frame", frame);
        cv::imshow("Red Mask", red_mask); // 빨간색 마스크만 표시
        cv::waitKey(1); // 1ms 대기 및 GUI 이벤트 처리
    }

    cv::VideoCapture cap_;
    rclcpp::Publisher<cv_msg::msg::MsgCenter>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    
    try
    {
        rclcpp::spin(std::make_shared<ColorDetectorNode>());
    }
    catch (const std::runtime_error& e)
    {
        RCLCPP_FATAL(rclcpp::get_logger("color_detector_node"), "Node execution stopped due to initialization failure: %s", e.what());
    }
    
    rclcpp::shutdown();
    return 0;
}