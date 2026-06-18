#include <rclcpp/rclcpp.hpp>
#include "cv_msg/srv/srv_addint.hpp" // 사용자 정의 서비스 헤더 포함
#include <memory>
#include <cstdlib>
#include <chrono>

using namespace std::chrono_literals;

// 서비스 클라이언트 노드 클래스
class AddIntsClient : public rclcpp::Node
{
public:
    AddIntsClient(int64_t a, int64_t b) : Node("add_two_ints_client")
    {
        // 서비스 클라이언트 생성. 서비스 이름은 "add_two_ints"로 가정
        client_ = this->create_client<cv_msg::srv::SrvAddint>("add_two_ints");
        RCLCPP_INFO(this->get_logger(), "Client Node created. Requesting service 'add_two_ints'.");

        // 요청할 두 숫자 저장
        a_ = a;
        b_ = b;
    }

    // 서버에 비동기적으로 요청을 보내는 함수
    void send_request()
    {
        // 1. 서버 대기
        // 서버가 준비될 때까지 최대 5초 대기
        while (!client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Client interrupted while waiting for service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Service not available yet, waiting...");
        }

        // 2. 요청 메시지 생성
        auto request = std::make_shared<cv_msg::srv::SrvAddint::Request>();
        request->a = a_;
        request->b = b_;

        RCLCPP_INFO(this->get_logger(), "Sending request: %ld + %ld", request->a, request->b);

        // 3. 비동기 요청 전송
        // Future 객체를 통해 응답을 기다립니다.
        auto result_future = client_->async_send_request(request);

        // 4. 응답 대기 및 결과 처리
        // 퓨처 객체가 완료될 때까지 ROS 2 스핀 (블로킹)
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result_future) ==
            rclcpp::FutureReturnCode::SUCCESS)
        {
            auto response = result_future.get();
            RCLCPP_INFO(this->get_logger(), 
                        "Received response: %ld + %ld = %ld", 
                        a_, b_, response->sum);
        } else {
            RCLCPP_ERROR(this->get_logger(), "Failed to call service 'add_two_ints'.");
        }
    }

private:
    rclcpp::Client<cv_msg::srv::SrvAddint>::SharedPtr client_;
    int64_t a_;
    int64_t b_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    // 요청할 두 숫자를 커맨드 라인 인수로 받습니다.
    if (argc != 3) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Usage: add_two_ints_client X Y");
        rclcpp::shutdown();
        return 1;
    }

    // 클라이언트 노드 생성 및 요청 전송
    auto client_node = std::make_shared<AddIntsClient>(atoll(argv[1]), atoll(argv[2]));
    client_node->send_request();

    rclcpp::shutdown();
    return 0;
}