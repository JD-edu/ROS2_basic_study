#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <libserial/SerialPort.h> // 1. libserial::SerialPort 헤더 사용
#include <string>
#include <memory>
#include <sstream> // std::stringstream 사용을 위해 추가

using std::placeholders::_1;
using namespace std::chrono_literals;

class SerialSubscriber : public rclcpp::Node
{
public:
    SerialSubscriber()
    : Node("serial_subscriber"),
      port_name_("/dev/ttyUSB0"),
      baud_rate_(LibSerial::BaudRate::BAUD_115200) // 2. BaudRate 타입을 LibSerial 타입으로 변경
    {
        // 1. 시리얼 포트 설정 및 초기화
        try {
            // SerialPort 객체를 사용하여 설정
            serial_port_.Open(port_name_);
            
            // 포트가 열리지 않았다면 예외를 던지지 않고 IsOpen()으로 확인 가능
            if (!serial_port_.IsOpen()) {
                RCLCPP_ERROR(this->get_logger(), "Failed to open serial port %s.", port_name_.c_str());
                // 여기서 노드를 종료하지 않고, 이후 콜백에서 통신을 막습니다.
                return;
            }

            // 3. 통신 속성 설정 (SerialPort 스타일)
            serial_port_.SetBaudRate(baud_rate_);
            serial_port_.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8); // 8N1 설정
            serial_port_.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
            serial_port_.SetParity(LibSerial::Parity::PARITY_NONE);
            serial_port_.SetStopBits(LibSerial::StopBits::STOP_BITS_1);
            
            // 4. 타임아웃 설정 (SerialPort는 Read/Write 타임아웃을 개별적으로 설정)
            serial_port_.SetVTime(0); // VTIME: Read 타임아웃 0 (즉시 반환)
            serial_port_.SetVMin(0);  // VMIN: 최소 문자 수 0

            RCLCPP_INFO(this->get_logger(), "Serial port %s opened successfully.", port_name_.c_str());

        } catch (const LibSerial::OpenFailed& e) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open serial port %s: %s", port_name_.c_str(), e.what());
        } 

        // 5. ROS 2 구독자 생성
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "cmd_vel",
            10,
            std::bind(&SerialSubscriber::listener_callback, this, _1)
        );
    }

    // 소멸자: 노드 종료 시 포트를 닫습니다.
    ~SerialSubscriber() 
    {
        if (serial_port_.IsOpen()) {
            serial_port_.Close();
        }
    }


private:
    void listener_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        // 수신된 linear.x 값 로깅
        RCLCPP_INFO(this->get_logger(), "I heard: '%.2f'", msg->linear.x);

        // 시리얼 포트가 열려 있는지 확인
        if (serial_port_.IsOpen()) {
            std::string command;

            // Python 로직과 동일하게 linear.x 값에 따라 명령 결정
            if (msg->linear.x >= 0.0) {
                command = "a";
            } else {
                command = "b";
            }
            
            // 시리얼로 명령 전송 (Write 함수 사용)
            try {
                // SerialPort의 Write 함수는 const std::string&을 인자로 받습니다.
                serial_port_.Write(command); 
                
                RCLCPP_DEBUG(this->get_logger(), "Sent serial command: %s", command.c_str());
            } catch (const LibSerial::NotOpen& e) {
                RCLCPP_ERROR(this->get_logger(), "Error writing to serial port (Not Open): %s", e.what());
            } 
        } else {
            RCLCPP_WARN_ONCE(this->get_logger(), "Serial port is not open. Command ignored.");
        }
    }

    // 멤버 변수
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    LibSerial::SerialPort serial_port_; // 2. SerialPort 객체
    std::string port_name_;
    const LibSerial::BaudRate baud_rate_; // 2. BaudRate 타입을 LibSerial 타입으로 변경
};

// 메인 함수는 기존과 동일
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto minimal_subscriber = std::make_shared<SerialSubscriber>();
    rclcpp::spin(minimal_subscriber);

    rclcpp::shutdown();
    return 0;
}