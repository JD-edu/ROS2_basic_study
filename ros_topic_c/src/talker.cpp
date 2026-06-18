#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <memory>
#include <string>

using namespace std::chrono_literals;

/**
 * HelloWorldPublisher 클래스
 * ROS2 퍼블리셔 노드를 구현하는 클래스
 */
class HelloWorldPublisher : public rclcpp::Node
{
public:
    /**
     * 생성자: 노드 이름과 퍼블리셔 설정
     */
    //HelloWorldPublisher() : Node("hello_world_publisher"), count_(0)
    HelloWorldPublisher() : Node("Hello_world_publisher")
    {
        
        count_ = 0;
        // 퍼블리셔 생성
        // 토픽명: "hello_world_topic"
        // 메시지 타입: std_msgs::msg::String
        // 큐 크기: 10
        publisher_ = this->create_publisher<std_msgs::msg::String>("hello_world_topic", 10);
        
        // 타이머 생성 (500ms마다 실행)
        timer_ = this->create_wall_timer(
            500ms, 
            std::bind(&HelloWorldPublisher::timer_callback, this)
        );
        
        RCLCPP_INFO(this->get_logger(), "Hello World Publisher 노드가 시작되었습니다.");
    }

private:
    /**
     * 타이머 콜백 함수
     * 주기적으로 호출되어 메시지를 발행
     */
    void timer_callback()
    {
        // 메시지 객체 생성
        auto message = std_msgs::msg::String();
        
        // 메시지 내용 설정
        message.data = "Hello World " + std::to_string(count_++);
        
        // 메시지 발행
        publisher_->publish(message);
        
        // 로그 출력
        RCLCPP_INFO(this->get_logger(), "발행된 메시지: '%s'", message.data.c_str());
    }
    
    // 멤버 변수
    rclcpp::TimerBase::SharedPtr timer_;                    // 타이머 객체
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;  // 퍼블리셔 객체
    size_t count_;                                          // 카운터 변수
};

/**
 * 메인 함수
 */
int main(int argc, char * argv[])
{
    // ROS2 초기화
    rclcpp::init(argc, argv);
    
    // 노드 생성 및 실행
    auto node = std::make_shared<HelloWorldPublisher>();
    
    RCLCPP_INFO(node->get_logger(), "Hello World Publisher를 시작합니다...");
    
    // 노드 실행 (블로킹)
    rclcpp::spin(node);
    
    // ROS2 종료
    rclcpp::shutdown();
    
    return 0;
}