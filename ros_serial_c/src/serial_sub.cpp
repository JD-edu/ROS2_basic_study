#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <memory>
#include <functional>

using std::placeholders::_1;

// 구독자 노드를 정의하는 클래스
class SerialSubscriberNode : public rclcpp::Node
{
public:
    // 생성자: 노드 이름 "serial_subscriber_node" 지정
    SerialSubscriberNode() : Node("serial_subscriber_node")
    {
        // "arduino_data" 토픽을 구독하고 콜백 함수(topic_callback)를 지정
        subscriber_ = this->create_subscription<std_msgs::msg::String>(
            "arduino_data", 
            10, 
            std::bind(&SerialSubscriberNode::topic_callback, this, _1)
        );
        RCLCPP_INFO(this->get_logger(), "Serial Subscriber Node started and listening to 'arduino_data'");
    }

private:
    // 구독한 메시지를 처리하는 콜백 함수
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        // 수신된 데이터를 콘솔에 출력
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }
    
    // 구독자 객체 포인터
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
};

int main(int argc, char * argv[])
{
    // ROS 2 초기화
    rclcpp::init(argc, argv);
    
    // SerialSubscriberNode의 인스턴스를 생성하고 ROS 2의 메인 루프에서 실행
    rclcpp::spin(std::make_shared<SerialSubscriberNode>());
    
    // ROS 2 종료
    rclcpp::shutdown();
    return 0;
}