#include <memory>
#include <string>
#include <vector>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

class RosArmBridge : public rclcpp::Node {
public:
    RosArmBridge() : Node("ros_arm_bridge") {
        // 파라미터 선언
        this->declare_parameter("port", "/dev/ttyUSB0");
        this->declare_parameter("baudrate", 115200);

        std::string port = this->get_parameter("port").as_string();
        int baud = this->get_parameter("baudrate").as_int();

        // 시리얼 포트 설정
        serial_port_ = open(port.c_str(), O_RDWR);
        if (serial_port_ < 0) {
            RCLCPP_ERROR(this->get_logger(), "Could not open serial port: %s", port.c_str());
            return;
        }

        struct termios tty;
        if (tcgetattr(serial_port_, &tty) != 0) {
            RCLCPP_ERROR(this->get_logger(), "Error from tcgetattr");
            return;
        }

        cfsetospeed(&tty, B115200);
        cfsetispeed(&tty, B115200);
        tty.c_cflag |= (CLOCAL | CREAD);
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;
        tty.c_cflag &= ~PARENB;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        tcsetattr(serial_port_, TCSANOW, &tty);

        // JointState 구독
        subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "joint_states", 10, std::bind(&RosArmBridge::joint_callback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Ros Arm C++ Bridge Started");
    }

    ~RosArmBridge() {
        if (serial_port_ >= 0) close(serial_port_);
    }

private:
    void joint_callback(const sensor_msgs::msg::JointState::SharedPtr msg) {
        // 라디안을 각도로 변환 (0~180도 제한)
        auto rad_to_deg = [](double rad) {
            int deg = static_cast<int>(rad * 180.0 / M_PI);
            if (deg < 0) deg = 0;
            if (deg > 180) deg = 180;
            return deg;
        };

        // 아두이노 코드 형식: a[val]b[val]c[val]d[val]e
        // joint_1 ~ joint_4 매핑 (인덱스는 URDF/메시지 순서에 의존)
        if (msg->position.size() >= 4) {
            int a = rad_to_deg(msg->position[0]);
            int b = rad_to_deg(msg->position[1]);
            int c = rad_to_deg(msg->position[2]);
            int d = rad_to_deg(msg->position[3]);

            std::string command = "a" + std::to_string(a) + 
                                  "b" + std::to_string(b) + 
                                  "c" + std::to_string(c) + 
                                  "d" + std::to_string(d) + "e";

            write(serial_port_, command.c_str(), command.size());
            // RCLCPP_INFO(this->get_logger(), "Sent: %s", command.c_str());
        }
    }

    int serial_port_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RosArmBridge>());
    rclcpp::shutdown();
    return 0;
}