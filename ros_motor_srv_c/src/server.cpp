#include <rclcpp/rclcpp.hpp>
#include "cv_msg/srv/srv_arduino.hpp" // 사용자 정의 서비스 헤더
#include <libserial/SerialStream.h>    // LibSerial 헤더
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unistd.h> // For usleep (if needed)

using SrvArduino = cv_msg::srv::SrvArduino;
using namespace LibSerial;

// 서비스 서버 노드 클래스
class MinimalService : public rclcpp::Node
{
public:
    MinimalService() : Node("minimal_service")
    {
        // 1. 시리얼 포트 초기화 및 개방 (Python: self.ser = serial.Serial('/dev/ttyACM0', 115200))
        const std::string port_name = "/dev/ttyACM0";
        const LibSerial::BaudRate baud_rate = LibSerial::BaudRate::BAUD_115200;

        serial_port_.Open(port_name);
        
        if (!serial_port_.good()) {
            RCLCPP_ERROR(this->get_logger(), "Error: Could not open serial port %s.", port_name.c_str());
            // 시리얼 포트 개방 실패 시 노드 실행 중지
            throw std::runtime_error("Serial port failed to open."); 
        }

        // 시리얼 설정
        serial_port_.SetBaudRate(baud_rate);
        serial_port_.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8); 
        serial_port_.SetParity(LibSerial::Parity::PARITY_NONE);       
        serial_port_.SetStopBits(LibSerial::StopBits::STOP_BITS_1);     
        serial_port_.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);

        RCLCPP_INFO(this->get_logger(), "Serial port %s opened successfully at 115200 baud.", port_name.c_str());
        
        // 2. 서비스 서버 생성 (Python: self.srv = self.create_service(...))
        service_ = this->create_service<SrvArduino>(
            "motor_con", 
            std::bind(&MinimalService::motor_callback, this, std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "Motor Control Service is ready on 'motor_con'.");
    }

    ~MinimalService()
    {
        if (serial_port_.IsOpen())
        {
            serial_port_.Close();
            RCLCPP_INFO(this->get_logger(), "Serial port closed.");
        }
    }

private:
    // 서비스 콜백 함수 (Python: def motor_callback)
    void motor_callback(
        const std::shared_ptr<SrvArduino::Request> request,
        const std::shared_ptr<SrvArduino::Response> response)
    {
        // 1. 명령 문자열 생성
        std::string command;
        std::stringstream ss;
        
        if (request->dir == 1) {
            // CW (Python: command = 'a'+str(request.speed)+'b')
            ss << 'a' << request->speed << 'b';
        } else if (request->dir == 2) {
            // CCW (Python: command = 'c'+str(request.speed)+'d')
            ss << 'c' << request->speed << 'd';
        } else if (request->dir == 0) {
            // Stop (Python: command = 'e'+str(request.speed)+'f')
            ss << 'e' << request->speed << 'f';
        } else {
            RCLCPP_WARN(this->get_logger(), "Invalid direction request: %ld", request->dir);
            response->answer = -1; // 에러 코드
            return;
        }

        command = ss.str();
        
        // 2. 시리얼 포트로 데이터 전송 (Python: self.ser.write(command.encode()))
        if (serial_port_.good() && serial_port_.IsOpen())
        {
            // LibSerial::SerialStream은 C++ iostream처럼 작동합니다.
            serial_port_ << command << std::flush;
            RCLCPP_INFO(this->get_logger(), "Serial command sent: '%s'", command.c_str());
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Serial port is not open. Command '%s' not sent.", command.c_str());
            response->answer = -2; // 시리얼 에러 코드
            return;
        }

        // 3. 응답 설정 및 로깅 (Python: response.answer = 45)
        response->answer = 45; 
        
        RCLCPP_INFO(this->get_logger(), 
                    "Incoming request processed. Direction: %ld, Speed: %ld, Reply: %ld", 
                    request->dir, request->speed, response->answer);
    }

    LibSerial::SerialStream serial_port_;
    rclcpp::Service<SrvArduino>::SharedPtr service_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    
    try
    {
        // MinimalService 인스턴스 생성 및 실행
        auto minimal_service = std::make_shared<MinimalService>();
        rclcpp::spin(minimal_service);
    }
    catch (const std::exception& e)
    {
        RCLCPP_FATAL(rclcpp::get_logger("minimal_service"), "Service node failed to start: %s", e.what());
    }
    
    rclcpp::shutdown();
    return 0;
}