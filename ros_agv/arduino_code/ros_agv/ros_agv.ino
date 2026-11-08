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

// Existing wiring: left inputs 12/10(PWM), right inputs 13/11(PWM).
// true: L9110 two-input bridge; false: DIR + active-high PWM interface.
const bool L9110_MODE = true;
const uint8_t LEFT_DIR = 12, LEFT_PWM = 10;
const uint8_t RIGHT_DIR = 13, RIGHT_PWM = 11;
const uint8_t LEFT_ENCODER = 2, RIGHT_ENCODER = 3;
// Change one polarity if that wheel rotates backward for a positive command.
const int8_t LEFT_POLARITY = 1, RIGHT_POLARITY = 1;
const uint8_t HEAD = 0xF5, CMD_MOTOR = 0x01, CMD_ENCODER = 0x03;
const unsigned long WATCHDOG_MS = 500, FEEDBACK_MS = 50;

volatile uint32_t leftTicks = 0, rightTicks = 0;
volatile int8_t leftDirection = 0, rightDirection = 0;
unsigned long lastCommand = 0, lastFeedback = 0, lastByte = 0;
uint8_t rx[6], used = 0;
bool driving = false;

// One pulse input per wheel: direction is inferred from the last motor command.
// These counters cannot detect external/manual reverse motion or coasting direction.
void leftEncoderISR() {
  if (leftDirection > 0) ++leftTicks;
  else if (leftDirection < 0) --leftTicks;
}
void rightEncoderISR() {
  if (rightDirection > 0) ++rightTicks;
  else if (rightDirection < 0) --rightTicks;
}

void setWheel(uint8_t directionPin, uint8_t pwmPin, int command) {
  int pwm = abs(command) * 255 / 100;
  // Zero PWM before changing direction to avoid a transient full-power command.
  analogWrite(pwmPin, 0);
  if (command == 0) {
    digitalWrite(directionPin, LOW);
    return;
  }
  if (L9110_MODE) {
    // input1=LOW/input2=PWM: forward; HIGH/inverted PWM: reverse.
    digitalWrite(directionPin, command < 0 ? HIGH : LOW);
    analogWrite(pwmPin, command < 0 ? 255 - pwm : pwm);
  } else {
    digitalWrite(directionPin, command > 0 ? HIGH : LOW);
    analogWrite(pwmPin, pwm);
  }
}

void setMotors(int8_t left, int8_t right) {
  noInterrupts();
  leftDirection = (left > 0) - (left < 0);
  rightDirection = (right > 0) - (right < 0);
  interrupts();
  static int previousLeft = 101, previousRight = 101;
  // Do not reset PWM on each heartbeat when the command has not changed.
  if (left != previousLeft) setWheel(LEFT_DIR, LEFT_PWM, left * LEFT_POLARITY);
  if (right != previousRight) setWheel(RIGHT_DIR, RIGHT_PWM, right * RIGHT_POLARITY);
  previousLeft = left;
  previousRight = right;
  driving = left != 0 || right != 0;
}

void acceptPacket() {
  // length = command(1) + two signed commands(2) + checksum(1).
  uint8_t checksum = uint8_t(rx[2] + rx[3] + rx[4]);
  int8_t left = int8_t(rx[3]), right = int8_t(rx[4]);
  if (rx[1] == 4 && rx[2] == CMD_MOTOR && rx[5] == checksum &&
      left >= -100 && left <= 100 && right >= -100 && right <= 100) {
    setMotors(left, right);
    lastCommand = millis();
  } else {
    setMotors(0, 0);
  }
}

void receiveCommands() {
  if (used && millis() - lastByte > 50) used = 0;
  // Bounded work preserves watchdog and feedback service under serial noise.
  for (uint8_t budget = 0; budget < 64 && Serial.available() > 0; ++budget) {
    uint8_t value = uint8_t(Serial.read());
    lastByte = millis();
    if (used == 0 && value != HEAD) continue;
    rx[used++] = value;
    if ((used == 2 && rx[1] != 4) || (used == 3 && rx[2] != CMD_MOTOR)) {
      used = value == HEAD ? 1 : 0;
      if (used) rx[0] = HEAD;
    }
    if (used == sizeof(rx)) {
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
