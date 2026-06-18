/*MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.*/

#include <SoftwareSerial.h>

// command protocol constant 
#define HEAD              0xf5
#define CMD_SET_MOTOR     0x01
#define CMD_GET_SPEED     0x02
#define CMD_GET_ENCODER   0x03
#define CMD_CAR_RUN       0x04

#define motor_A_enable 12
#define motor_B_enable 13
#define motor_A 10
#define motor_B 11

// encoder pin definition 
#define encoder_A 2
#define encoder_B 3  // left from view of robot 

// Using softserial as debugging. Arduino Uno has only 1 serial port. 
SoftwareSerial Serial2(7,8);

// Step 4 for motor control, in this code, using L9110 motor driver IC 
// Using pin 5, 6 pwm enabled pins 
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial2.println("hello...");
  pinMode(13, OUTPUT);
  pinMode(motor_A_enable, OUTPUT);
  pinMode(motor_B_enable, OUTPUT);
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);

  // 엔코더 핀 입력 설정 및 인터럽트 연결
  pinMode(encoder_A, INPUT);
  pinMode(encoder_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder_A), encoder_A_ISR, RISING); // A채널 상승 시 인터럽트 발생
  attachInterrupt(digitalPinToInterrupt(encoder_B), encoder_B_ISR, RISING); // A채널 상승 시 인터럽트 발생
}

void byte_to_hex(byte a){
  char hexString[3];
  sprintf(hexString, "%02X", a);
  // Serial2.println(hexString);  // for debugging 
}

void motorForward(int speed_A, int speed_B) {
  digitalWrite(motor_A_enable, HIGH);
  digitalWrite(motor_B_enable, HIGH);
  analogWrite(motor_A, speed_A);
  analogWrite(motor_B, speed_B);
}

void motorBackward(int speed_A, int speed_B) {
  digitalWrite(motor_A_enable, LOW);
  digitalWrite(motor_B_enable, LOW);
  analogWrite(motor_A, speed_A);
  analogWrite(motor_B, speed_B);
}

// 모터 정지 함수
void motorStop() {
  digitalWrite(motor_A_enable, LOW);
  digitalWrite(motor_B_enable, LOW);
  analogWrite(motor_A, 0);
  analogWrite(motor_B, 0);
}


/* 
Encoder variable
We should use long data type. Arduino long data type is 4 bytes.
Arduino int data type is 2 bytes. 
*/
long lf_encoder = 0;        // left front encoder value 
long rf_encoder = 0;        // right fron encoder value 
long lr_encoder = 0;        // left rear encoder value 
long rr_encoder = 0;        // right rear encoder value

void loop(){ 
  // Step2 receiving and parsing of command packet from PC
   if(Serial.available() > 0){
    // Header byte 
    byte c = Serial.read();   //HEAD
    byte_to_hex(c);
    if( c == HEAD){
      c = Serial.read();      //length 
      byte_to_hex(c);
      c = Serial.read();        //command
      byte_to_hex(c);
      if(c == CMD_SET_MOTOR){
        byte lf = Serial.read();    //speed 1 
        // We use left-front wheel. ROS send speed data. It controls left-front wheel.
        if(lf > 0){
          go_forward(lf);
        }else if(lf < 0){
          go_backward(lf*-1);
        }else{
          stop();
        }
        byte_to_hex(lf);
        byte rf = Serial.read();    //speed 2
        byte_to_hex(rf);
        byte lr = Serial.read();    //speed 3
        byte_to_hex(lr);
        byte rr = Serial.read();    //speed 4  
        byte_to_hex(rr);
        c = Serial.read();          // checksum   
        byte_to_hex(c);
        Serial2.print("Motor: ");
        Serial2.print(lf);
        Serial2.print(" ");
        Serial2.print(lr);
        Serial2.print(" ");
        Serial2.print(rf);
        Serial2.print(" ");
        Serial2.println(rr);
        
      }
    }
  }
  // Encoder value simulation 
  lf_encoder += 100;
  Serial2.print( " LF:" );      // print for debugging 
  Serial2.print( lf_encoder );
  Serial2.print( " RF:" );
  Serial2.print( rf_encoder );
  Serial2.print( " LR:" );
  Serial2.print( lr_encoder );
  Serial2.print( " RR:" );
  Serial2.println( rr_encoder );
 
  byte data_buffer[20] = {0};   // Command packer container 
  byte i, checknum = 0;
  data_buffer[0] = 0xf5;                          // HEADER 
  data_buffer[1] = 19;                            // length 
  data_buffer[2] = 0x03;                          // command 
  data_buffer[3] = (lf_encoder >> 24) & 0xff;     // payload 
  data_buffer[4] = (lf_encoder >> 16) & 0xff;     // long 4 bytes as byte array 
  data_buffer[5] = (lf_encoder >> 8) & 0xff;
  data_buffer[6] = lf_encoder & 0xff;
  data_buffer[7] = (rf_encoder >> 24) & 0xff;
  data_buffer[8] = (rf_encoder >> 16) & 0xff;
  data_buffer[9] = (rf_encoder >> 8) & 0xff;
  data_buffer[10] = rf_encoder  & 0xff;
  data_buffer[11] = (lr_encoder >> 24) & 0xff;
  data_buffer[12] = (lr_encoder >> 16) & 0xff;
  data_buffer[13] = (lr_encoder >> 8) & 0xff;
  data_buffer[14] = lr_encoder  & 0xff;
  data_buffer[15] = (rr_encoder >> 24) & 0xff;
  data_buffer[16] = (rr_encoder >> 16) & 0xff;
  data_buffer[17] = (rr_encoder >> 8) & 0xff;
  data_buffer[18] = rr_encoder  & 0xff;
 for (i = 2; i < 19; i++)
  {
    checknum += data_buffer[i];
  }
  data_buffer[19] = checknum;           
  Serial.write(data_buffer, 20);  // Sending command packets 
  delay(500);
}
