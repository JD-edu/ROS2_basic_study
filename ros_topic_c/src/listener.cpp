#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <memory>

/**
 * HelloWorldSubscriber 클래스
 * ROS2 서브스크라이버 노드를 구현하는 클래스
 */
class HelloWorldSubscriber : public rclcpp::Node
{
public:
    /**
     * 생성자: 노드 이름과 서브스크라이버 설정
     */
    HelloWorldSubscriber() : Node("hello_world_subscriber")
    {
        // 서브스크라이버 생성
        // 토픽명: "hello_world_topic"
        // 메시지 타입: std_msgs::msg::String
        // 큐 크기: 10
        // 콜백 함수: topic_callback
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "hello_world_topic", 
            10,
            std::bind(&HelloWorldSubscriber::topic_callback, this, std::placeholders::_1)
        );
        
        RCLCPP_INFO(this->get_logger(), "Hello World Subscriber 노드가 시작되었습니다.");
        RCLCPP_INFO(this->get_logger(), "'hello_world_topic' 토픽을 구독하고 있습니다.");
    }

private:
    /**
     * 토픽 콜백 함수
     * 메시지가 수신될 때마다 호출됨
     * 
     * @param msg 수신된 메시지 객체
     */
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        // 수신된 메시지 로그 출력
        RCLCPP_INFO(this->get_logger(), "수신된 메시지: '%s'", msg->data.c_str());
        
        // 추가 처리 로직을 여기에 구현 가능
        // 예: 파일 저장, 다른 토픽 발행, 서비스 호출 등
    }
    
    // 멤버 변수
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;  // 서브스크라이버 객체
};

/**
 * 메인 함수
 */
int main(int argc, char * argv[])
{
    // ROS2 초기화
    rclcpp::init(argc, argv);
    
    // 노드 생성 및 실행
    auto node = std::make_shared<HelloWorldSubscriber>();
    
    RCLCPP_INFO(node->get_logger(), "Hello World Subscriber를 시작합니다...");
    RCLCPP_INFO(node->get_logger(), "메시지를 기다리는 중... (Ctrl+C로 종료)");
    
    // 노드 실행 (블로킹)
    rclcpp::spin(node);
    
    // ROS2 종료
    rclcpp::shutdown();
    
    return 0;
}