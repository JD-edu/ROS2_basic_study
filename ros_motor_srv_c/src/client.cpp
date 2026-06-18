#include <rclcpp/rclcpp.hpp>
#include "cv_msg/srv/srv_arduino.hpp" // 사용자 정의 서비스 헤더
#include <memory>
#include <chrono>
#include <cstdlib>
#include <string>

using namespace std::chrono_literals;

using SrvArduino = cv_msg::srv::SrvArduino;

// 서비스 클라이언트 노드 클래스
class MinimalClientAsync : public rclcpp::Node
{
public:
    MinimalClientAsync(int64_t direction, int64_t speed) : 
        Node("minimal_client_async"),
        dir_(direction),
        speed_(speed)
    {
        // 1. 클라이언트 생성
        client_ = this->create_client<SrvArduino>("motor_con");

        // 2. 서버 대기 (Python 코드의 while not self.cli.wait_for_service...)
        RCLCPP_INFO(this->get_logger(), "Waiting for service 'motor_con'...");
        
        while (!client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Client interrupted while waiting for service. Exiting.");
                return;
            }
            RCLCPP_WARN(this->get_logger(), "Service not available, waiting again...");
        }
        RCLCPP_INFO(this->get_logger(), "Service is available. Ready to send request.");
    }

    // 서비스 요청을 비동기적으로 보내는 함수
    rclcpp::Client<SrvArduino>::FutureAndRequestId send_request()
    {
        // 1. 요청 메시지 생성 및 데이터 할당
        auto request = std::make_shared<SrvArduino::Request>();
        request->dir = dir_;
        request->speed = speed_;

        RCLCPP_INFO(this->get_logger(), "Sending request: Direction = %ld, Speed = %ld", 
                    request->dir, request->speed);

        // 2. 비동기 요청 전송
        return client_->async_send_request(request);
    }

private:
    rclcpp::Client<SrvArduino>::SharedPtr client_;;
    int64_t dir_;
    int64_t speed_;
};

int main(int argc, char * argv[])
{
    // 1. ROS 2 초기화
    rclcpp::init(argc, argv);

    // 2. 명령줄 인수 확인 및 파싱 (Python sys.argv[1], sys.argv[2])
    if (argc != 3) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Usage: minimal_client_async <dir> <speed>");
        rclcpp::shutdown();
        return 1;
    }

    int64_t dir = std::stoll(argv[1]);
    int64_t speed = std::stoll(argv[2]);

    // 3. 클라이언트 노드 생성
    auto minimal_client = std::make_shared<MinimalClientAsync>(dir, speed);

    // 4. 요청 전송 및 Future 객체 받기
    auto future = minimal_client->send_request();

    // 5. 응답 대기 및 결과 처리 (Python rclpy.spin_until_future_complete)
    rclcpp::spin_until_future_complete(minimal_client, future);

    // 6. 결과 출력 (Python response = future.result() 및 print)
    if (future.wait_for(0s) == std::future_status::ready)
    {
        auto response = future.get();
        RCLCPP_INFO(minimal_client->get_logger(),
            "Answer of motor control is direction: %ld speed: %ld return value: %ld",
            dir, speed, response->answer);
    } else {
        RCLCPP_ERROR(minimal_client->get_logger(), "Service call failed or timed out.");
    }

    // 7. 노드 종료 (Python minimal_client.destroy_node() 및 rclpy.shutdown())
    rclcpp::shutdown();
    return 0;
}