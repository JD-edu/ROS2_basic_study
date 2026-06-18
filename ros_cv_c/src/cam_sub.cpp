#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImageSubscriber : public rclcpp::Node
{
public:
    ImageSubscriber()
    : Node("image_subscriber")
    {
        // OpenCV 창을 미리 생성합니다.
        cv::namedWindow(OPENCV_WINDOW, cv::WINDOW_AUTOSIZE);
        
        // 구독자 생성: "camera/image" 토픽에서 sensor_msgs::msg::Image 메시지를 받습니다.
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "camera/image",
            10, // QoS 큐 사이즈
            std::bind(&ImageSubscriber::image_callback, this, std::placeholders::_1)
        );

        RCLCPP_INFO(this->get_logger(), "Image Subscriber Node started, waiting for images on 'camera/image' topic.");
    }

    ~ImageSubscriber()
    {
        // 노드가 종료될 때 OpenCV 창을 닫습니다.
        cv::destroyWindow(OPENCV_WINDOW);
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        
        try
        {
            // ROS Image 메시지를 OpenCV Mat으로 변환합니다.
            // msg->encoding을 사용하여 메시지의 인코딩 정보(예: bgr8)를 그대로 사용합니다.
            cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        // 1. 이미지 처리 (예시: 화면 중앙에 작은 원 그리기)
        cv::circle(cv_ptr->image, cv::Point(cv_ptr->image.cols / 2, cv_ptr->image.rows / 2), 20, CV_RGB(255, 0, 0), 2);

        // 2. OpenCV 창에 이미지 표시
        cv::imshow(OPENCV_WINDOW, cv_ptr->image);

        // 3. 창을 업데이트하고 키 입력을 처리합니다. (GUI가 작동하도록 필수)
        cv::waitKey(3); 
        
        RCLCPP_INFO(this->get_logger(), "Received image. Time stamp: %f", this->now().seconds());
    }

    // 멤버 변수 선언
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    const std::string OPENCV_WINDOW = "Webcam Feed";
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ImageSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}