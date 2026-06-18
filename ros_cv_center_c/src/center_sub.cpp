#include <rclcpp/rclcpp.hpp>

// 사용자 정의 메시지 헤더 포함
#include "cv_msg/msg/msg_center.hpp"
#include <memory>
#include <functional>

using std::placeholders::_1;
using CenterMsg = cv_msg::msg::MsgCenter;

// 구독자 노드를 정의하는 클래스
class CenterPointSubscriberNode : public rclcpp::Node
{
public:
    // 생성자: 노드 이름 "center_point_subscriber_node" 지정
    CenterPointSubscriberNode() : Node("center_point_subscriber_node")
    {
        // "red_center" 토픽을 구독하고 콜백 함수(center_callback)를 지정
        subscription_ = this->create_subscription<CenterMsg>(
            "red_center", 
            10, 
            std::bind(&CenterPointSubscriberNode::center_callback, this, _1)
        );
        RCLCPP_INFO(this->get_logger(), "Center Point Subscriber Node started and listening to 'red_center'.");
    }

private:
    // 구독한 메시지를 처리하는 콜백 함수
    void center_callback(const CenterMsg::SharedPtr msg) const
    {
        // 수신된 중심점 좌표 데이터 출력
        if (msg->x == -1 && msg->y == -1) {
            RCLCPP_INFO(this->get_logger(), "Center Point: Not detected (x: -1, y: -1)");
        } else {
            RCLCPP_INFO(this->get_logger(), 
                        "Center Point Detected: (X: %ld, Y: %ld)", 
                        msg->x, 
                        msg->y);
        }
    }
    
    // 구독자 객체 포인터
    rclcpp::Subscription<CenterMsg>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    // ROS 2 초기화
    rclcpp::init(argc, argv);
    
    // 노드 인스턴스를 생성하고 ROS 2의 메인 루프에서 실행
    rclcpp::spin(std::make_shared<CenterPointSubscriberNode>());
    
    // ROS 2 종료
    rclcpp::shutdown();
    return 0;
}