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

// 실제 모터 대신 내장 LED를 사용합니다.
// LED ON = 한쪽 이상 구동, LED OFF = 정지. 바퀴별 가상 엔코더를 생성합니다.
const uint8_t HEAD = 0xF5, CMD_MOTOR = 0x01, CMD_ENCODER = 0x03;
const unsigned long WATCHDOG_MS = 500;
const unsigned long FEEDBACK_MS = 50;
// ROS 드라이버와 같은 바퀴 사양: 최대 0.5m/s, 반지름 0.075m, 1320 ticks/rev.
const float TICKS_PER_COMMAND_MS = 0.5f * 1320.0f / (2.0f * PI * 0.075f * 100.0f * 1000.0f);
float leftRemainder = 0, rightRemainder = 0;

uint32_t leftTicks = 0, rightTicks = 0;
unsigned long lastCommand = 0, lastFeedback = 0;
uint8_t rx[6], used = 0;
bool driving = false;
int8_t leftCommand = 0, rightCommand = 0;

void integrateEncoders(unsigned long now) {
  static unsigned long previous = 0;
  unsigned long elapsed = now - previous;
  previous = now;
  leftRemainder += leftCommand * (float)elapsed * TICKS_PER_COMMAND_MS;
  rightRemainder += rightCommand * (float)elapsed * TICKS_PER_COMMAND_MS;
  int32_t leftDelta = (int32_t)leftRemainder;
  int32_t rightDelta = (int32_t)rightRemainder;
  // 부호 있는 이동량을 32비트 모듈러 카운터에 저장합니다(후진 시 감소).
  leftTicks += (uint32_t)leftDelta;
  rightTicks += (uint32_t)rightDelta;
  leftRemainder -= leftDelta;
  rightRemainder -= rightDelta;
}

void setMotors(int8_t left, int8_t right) {
  // 명령 변경 전까지는 이전 속도로 적분합니다. 워치독 이후 시간은 정지 처리합니다.
  unsigned long now = millis();
  if (driving && now - lastCommand > WATCHDOG_MS) {
    integrateEncoders(lastCommand + WATCHDOG_MS);
    leftCommand = rightCommand = 0;
  }
  integrateEncoders(now);
  leftCommand = left;
  rightCommand = right;
  driving = left != 0 || right != 0;
  digitalWrite(LED_BUILTIN, driving ? HIGH : LOW);
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
  // 한 주기에서 대기 중인 명령을 모두 처리합니다.
  while (Serial.available() > 0) {
    uint8_t value = Serial.read();

    // 패킷의 첫 바이트는 반드시 헤더(0xF5)여야 합니다.
    if (used == 0 && value != HEAD) {
      continue;
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
  uint32_t left = leftTicks;
  uint32_t right = rightTicks;
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
  pinMode(LED_BUILTIN, OUTPUT);
  setMotors(0, 0);
  Serial.begin(115200);
}

void loop() {
  // Python 또는 ROS 노드의 6바이트 모터 명령을 받습니다.
  receiveCommands();

  unsigned long now = millis();
  if (driving && now - lastCommand >= WATCHDOG_MS) {
    setMotors(0, 0);  // 명령이 끊기면 LED를 끄고 카운트를 멈춥니다.
  }

  // 정지 중에도 엔코더 패킷을 보내야 Python/ROS에서 통신을 확인할 수 있습니다.
  if (now - lastFeedback >= FEEDBACK_MS) {
    lastFeedback = now;
    integrateEncoders(now);
    sendEncoders();
  }
}
