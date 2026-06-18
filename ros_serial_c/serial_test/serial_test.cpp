/*
sudo apt update 
sudo apt install libserial-dev
g++ serial_test.cpp -o serial_app -I/usr/include/libserial -L/usr/local/lib -lserial
*/
#include <SerialStream.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream> // for stringstream

using namespace std;
using namespace LibSerial;

int main()
{
    // 1. Setup
    // CHANGE THIS to your actual serial port 
    const char* const SERIAL_PORT_DEVICE = "/dev/ttyUSB0"; 
    
    // Create a SerialStream object
    SerialStream serial_port;

    // Open the serial port
    serial_port.Open(SERIAL_PORT_DEVICE);

    if (!serial_port.good()) {
        cerr << "Error: Could not open serial port " << SERIAL_PORT_DEVICE << endl;
        return 1;
    }

    // Set Serial Port Parameters (8N1 @ 9600 baud)
    serial_port.SetBaudRate(LibSerial::BaudRate::BAUD_115200); 
    serial_port.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8); 
    serial_port.SetParity(LibSerial::Parity::PARITY_NONE);       
    serial_port.SetStopBits(LibSerial::StopBits::STOP_BITS_1);     
    serial_port.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);

    // Turn off skipping of whitespace characters
    serial_port.unsetf(std::ios_base::skipws);
    
    // Wait for the port to stabilize
    usleep(100000); 

    // 2. Send a command (Optional, but useful to trigger a device response)
    string command = "GET_DATA\n";
    cout << "Sending command: " << command;
    serial_port << command << flush; 

    // Wait a brief moment for a response to start coming back
    usleep(500000); // 500 milliseconds

    // 3. Receive Data
    cout << "Waiting for response..." << endl;
    
    // Check if data is available in the input buffer
    if (serial_port.rdbuf()->in_avail() == 0) {
        cout << "No data immediately available. Waiting a bit longer..." << endl;
        // You might add a loop here with a timeout for production code.
    }
    
    stringstream received_data;
    char next_byte;
    
    // Read data byte by byte until the stream fails (e.g., timeout) or buffer is empty.
    while(true){
            while (serial_port.get(next_byte)) 
        {
            received_data << next_byte;
            
            // OPTIONAL: Stop reading if a newline character is found
            if (next_byte == '\n') {
                break; 
            }
            
            // This is necessary to yield some CPU time and avoid spinning too fast
            usleep(1000); 
        }

        // 4. Output and Cleanup
        cout << "\n--- Received Data ---" << endl;
        cout << received_data.str() << endl;
        cout << "---------------------" << endl;

    }
    
    serial_port.Close();
    return 0;
}