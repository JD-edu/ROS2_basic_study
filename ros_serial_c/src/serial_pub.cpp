#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <libserial/SerialPort.h>
#include <string>
#include <chrono>
#include <memory>

using namespace LibSerial;
using namespace std::chrono_literals;

class SerialReaderNode : public rclcpp::Node
{
public:
    SerialReaderNode() : Node("serial_reader_node")
    {
        // Declare parameters
        this->declare_parameter<std::string>("serial_port", "/dev/ttyUSB0");
        this->declare_parameter<int>("baud_rate", 115200);
        this->declare_parameter<int>("timeout_ms", 1000);
        
        // Get parameters
        std::string port_name = this->get_parameter("serial_port").as_string();
        int baud_rate = this->get_parameter("baud_rate").as_int();
        int timeout_ms = this->get_parameter("timeout_ms").as_int();
        
        // Initialize publisher
        publisher_ = this->create_publisher<std_msgs::msg::String>("arduino_data", 10);
        
        // Initialize serial port
        try
        {
            serial_port_.Open(port_name);
            
            // Set baud rate
            BaudRate serial_baud_rate;
            switch(baud_rate)
            {
                case 9600:   serial_baud_rate = BaudRate::BAUD_9600; break;
                case 19200:  serial_baud_rate = BaudRate::BAUD_19200; break;
                case 38400:  serial_baud_rate = BaudRate::BAUD_38400; break;
                case 57600:  serial_baud_rate = BaudRate::BAUD_57600; break;
                case 115200: serial_baud_rate = BaudRate::BAUD_115200; break;
                default:     serial_baud_rate = BaudRate::BAUD_9600; break;
            }
            
            serial_port_.SetBaudRate(serial_baud_rate);
            serial_port_.SetCharacterSize(CharacterSize::CHAR_SIZE_8);
            serial_port_.SetFlowControl(FlowControl::FLOW_CONTROL_NONE);
            serial_port_.SetParity(Parity::PARITY_NONE);
            serial_port_.SetStopBits(StopBits::STOP_BITS_1);
            
            RCLCPP_INFO(this->get_logger(), "Serial port %s opened successfully at %d baud", 
                       port_name.c_str(), baud_rate);
        }
        catch(const OpenFailed& e)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open serial port %s: %s", 
                        port_name.c_str(), e.what());
            return;
        }
        
        // Create timer for reading serial data
        timer_ = this->create_wall_timer(
            10ms, std::bind(&SerialReaderNode::read_serial_data, this));
            
        RCLCPP_INFO(this->get_logger(), "Serial Reader Node started");
    }
    
    ~SerialReaderNode()
    {
        if(serial_port_.IsOpen())
        {
            serial_port_.Close();
            RCLCPP_INFO(this->get_logger(), "Serial port closed");
        }
    }

private:
    void read_serial_data()
    {
        if(!serial_port_.IsOpen())
        {
            return;
        }
        
        try
        {
            // Check if data is available
            if(serial_port_.IsDataAvailable())
            {
                std::string received_data;
                
                // Read line (until newline character)
                serial_port_.ReadLine(received_data, '\n', 1000); // 1000ms timeout
                
                if(!received_data.empty())
                {
                    // Remove carriage return and newline characters
                    received_data.erase(std::remove(received_data.begin(), 
                                                  received_data.end(), '\r'), 
                                      received_data.end());
                    received_data.erase(std::remove(received_data.begin(), 
                                                  received_data.end(), '\n'), 
                                      received_data.end());
                    
                    // Create and publish message
                    auto message = std_msgs::msg::String();
                    message.data = received_data;
                    publisher_->publish(message);
                    
                    RCLCPP_INFO(this->get_logger(), "Received: '%s'", received_data.c_str());
                }
            }
        }
        catch(const ReadTimeout& e)
        {
            // Timeout is normal, just continue
        }
        catch(const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "Error reading serial data: %s", e.what());
        }
    }
    
    SerialPort serial_port_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<SerialReaderNode>();
    
    try
    {
        rclcpp::spin(node);
    }
    catch(const std::exception& e)
    {
        RCLCPP_ERROR(rclcpp::get_logger("serial_reader_node"), 
                    "Exception in main: %s", e.what());
    }
    
    rclcpp::shutdown();
    return 0;
}