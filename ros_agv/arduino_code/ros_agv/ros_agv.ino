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

#include <Arduino.h>

// 모터마다 방향(DIR) 핀과 속도(PWM) 핀을 사용합니다.
const uint8_t LEFT_DIR = 12, LEFT_PWM = 10;
const uint8_t RIGHT_DIR = 13, RIGHT_PWM = 11;
const uint8_t LEFT_ENCODER = 2, RIGHT_ENCODER = 3;
// Change one polarity if that wheel rotates backward for a positive command.
const int8_t LEFT_POLARITY = 1, RIGHT_POLARITY = 1;
const uint8_t HEAD = 0xF5, CMD_MOTOR = 0x01, CMD_ENCODER = 0x03;
const unsigned long WATCHDOG_MS = 500, FEEDBACK_MS = 50;

volatile uint32_t leftTicks = 0, rightTicks = 0;
unsigned long lastCommand = 0, lastFeedback = 0;
uint8_t rx[6], used = 0;
bool driving = false;

// Single-channel encoder: every pulse adds one, regardless of motor direction.
void leftEncoderISR() { ++leftTicks; }
void rightEncoderISR() { ++rightTicks; }

void setWheel(uint8_t directionPin, uint8_t pwmPin, int command) {
  int pwm = abs(command) * 255 / 100;
  if (command == 0) {
    analogWrite(pwmPin, 0);
    digitalWrite(directionPin, LOW);
    return;
  }
  // 양수는 전진, 음수는 후진입니다.
  if (command > 0) {
    digitalWrite(directionPin, HIGH);
  } else {
    digitalWrite(directionPin, LOW);
  }
  analogWrite(pwmPin, pwm);
}

// left, right: -100(후진) ~ 0(정지) ~ 100(전진)
void setMotors(int8_t left, int8_t right) {
  // 왼쪽과 오른쪽 모터에 각각 속도를 전달합니다.
  setWheel(LEFT_DIR, LEFT_PWM, left * LEFT_POLARITY);
  setWheel(RIGHT_DIR, RIGHT_PWM, right * RIGHT_POLARITY);

  // 두 모터가 모두 0이면 정지 상태입니다.
  if (left == 0 && right == 0) {
    driving = false;
  } else {
    driving = true;
  }
}

void acceptPacket() {
  // rx: [헤더, 길이, 명령, 왼쪽 속도, 오른쪽 속도, 체크섬]

  // 1. 길이와 명령을 확인합니다.
  if (rx[1] != 4 || rx[2] != CMD_MOTOR) {
    setMotors(0, 0);
    return;
  }

  // 2. 명령과 두 속도의 합으로 체크섬을 확인합니다.
  // uint8_t에 저장하면 합의 하위 8비트(0~255)만 남습니다.
  uint8_t checksum = rx[2] + rx[3] + rx[4];
  if (rx[5] != checksum) {
    setMotors(0, 0);
    return;
  }

  // 3. 속도를 음수가 가능한 값으로 읽고 범위를 확인합니다.
  int8_t left = (int8_t)rx[3];
  int8_t right = (int8_t)rx[4];
  if (left < -100 || left > 100 || right < -100 || right > 100) {
    setMotors(0, 0);
    return;
  }

  // 4. 모터를 제어하고 마지막 명령 시간을 기록합니다.
  setMotors(left, right);
  lastCommand = millis();
}

void receiveCommands() {
  // 수신된 데이터가 있을 때만 한 바이트 읽습니다.
  if (Serial.available() > 0) {
    uint8_t value = Serial.read();

    // 패킷의 첫 바이트는 반드시 헤더(0xF5)여야 합니다.
    if (used == 0 && value != HEAD) {
      return;
    }

    // 읽은 바이트를 차례대로 저장합니다.
    rx[used] = value;
    used++;

    // 6바이트가 모이면 명령을 처리하고 다음 패킷을 받습니다.
    if (used == 6) {
      acceptPacket();
      used = 0;
    }
  }
}

void sendEncoders() {
  uint32_t left, right;
  noInterrupts();
  left = leftTicks;
  right = rightTicks;
  interrupts();
  uint8_t packet[12] = {HEAD, 10, CMD_ENCODER};
  for (uint8_t i = 0; i < 4; ++i) {
    packet[3 + i] = uint8_t(left >> (24 - 8 * i));
    packet[7 + i] = uint8_t(right >> (24 - 8 * i));
  }
  uint8_t checksum = 0;
  for (uint8_t i = 2; i < 11; ++i) checksum += packet[i];
  packet[11] = checksum;
  Serial.write(packet, sizeof(packet));
}

void setup() {
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  setMotors(0, 0);
  pinMode(LEFT_ENCODER, INPUT_PULLUP);
  pinMode(RIGHT_ENCODER, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), rightEncoderISR, RISING);
  Serial.begin(115200);
}

void loop() {
  receiveCommands();
  unsigned long now = millis();
  if (driving && now - lastCommand >= WATCHDOG_MS) setMotors(0, 0);
  if (now - lastFeedback >= FEEDBACK_MS) {
    lastFeedback = now;
    sendEncoders();
  }
}
