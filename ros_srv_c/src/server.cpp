#include <rclcpp/rclcpp.hpp>
#include "cv_msg/srv/srv_addint.hpp" // 사용자 정의 서비스 헤더 포함
#include <memory>
#include <functional>

using SrvAddint = cv_msg::srv::SrvAddint; // 짧은 이름으로 별칭 지정

// 서버 역할을 수행하는 콜백 함수
// 서비스 요청(Request)을 받아 처리하고 응답(Response)을 채웁니다.
void add(const std::shared_ptr<SrvAddint::Request> request,
         const std::shared_ptr<SrvAddint::Response> response)
{
    // 요청의 두 숫자(a와 b)를 더합니다.
    response->sum = request->a + request->b;
    
    // 로그에 계산 과정을 기록합니다.
    RCLCPP_INFO(rclcpp::get_logger("add_two_ints_server"), 
                "Incoming request: a = %ld, b = %ld", 
                request->a, request->b);
    RCLCPP_INFO(rclcpp::get_logger("add_two_ints_server"), 
                "Sending back response: sum = %ld", 
                response->sum);
}

int main(int argc, char * argv[])
{
    // ROS 2 초기화
    rclcpp::init(argc, argv);
    
    // 노드 생성
    std::shared_ptr<rclcpp::Node> node = 
        std::make_shared<rclcpp::Node>("add_two_ints_server");

    // 서비스 서버 생성
    // 서비스 타입: cv_msg::srv::SrvAddInt
    // 서비스 이름: "add_two_ints"
    // 콜백 함수: add
    rclcpp::Service<SrvAddint>::SharedPtr service =
        node->create_service<SrvAddint>("add_two_ints", &add);

    RCLCPP_INFO(node->get_logger(), "Ready to add two ints.");

    // 노드의 서비스 콜백이 들어올 때까지 계속 스핀합니다.
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}