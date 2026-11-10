"""Execute the actual simulation sketch with a minimal Arduino host shim."""
from pathlib import Path
import shutil
import subprocess

import pytest


def test_simulation_commands_feedback_and_watchdog(tmp_path):
    compiler = shutil.which('g++')
    if compiler is None:
        pytest.skip('g++ is required for the firmware host test')
    (tmp_path / 'Arduino.h').write_text('''
#include <cstdint>
#include <deque>
#include <vector>
#include <cassert>
#define PI 3.14159265358979323846
#define LED_BUILTIN 13
#define OUTPUT 1
#define HIGH 1
#define LOW 0
unsigned long clockMs = 0;
unsigned long millis() { return clockMs; }
void pinMode(int, int) {}
void digitalWrite(int, int) {}
struct SerialMock {
  std::deque<uint8_t> input;
  std::vector<uint8_t> output;
  void begin(int) {}
  int available() { return input.size(); }
  uint8_t read() { auto v = input.front(); input.pop_front(); return v; }
  void write(const uint8_t *p, unsigned int n) { output.assign(p, p+n); }
} Serial;
''')
    sketch = Path(__file__).resolve().parents[1] / (
        'arduino_code/ros_agv_simulation/ros_agv_simulation.ino')
    source = tmp_path / 'test.cpp'
    source.write_text('#include "' + str(sketch) + '"\n' + '''
void command(int left, int right) {
  uint8_t l = left, r = right;
  for (auto b : std::vector<uint8_t>{245,4,1,l,r,uint8_t(1+l+r)})
    Serial.input.push_back(b);
}
void tick() { clockMs += 50; loop(); }
int main() {
  setup();
  tick(); assert(leftTicks == 0 && rightTicks == 0);
  command(20,20); loop(); tick();
  assert(leftTicks == 14 && rightTicks == 14);
  command(-20,-20); loop(); tick();
  assert(leftTicks == 0 && rightTicks == 0);
  command(-20,20); loop(); tick();
  assert(int32_t(leftTicks) == -14 && rightTicks == 14);
  command(20,-20); loop(); tick();
  assert(leftTicks == 0 && rightTicks == 0);
  command(0,40); loop(); tick();
  assert(leftTicks == 0 && rightTicks == 28);
  command(0,0); loop(); tick();
  assert(leftTicks == 0 && rightTicks == 28);
  command(20,20); loop(); tick();
  clockMs += 500; loop(); assert(!driving);
  // 500ms 명령 유효 구간까지만 적분합니다.
  assert(leftTicks == 140 && rightTicks == 168);
  auto left = leftTicks, right = rightTicks;
  tick(); assert(leftTicks == left && rightTicks == right);
  assert(Serial.output.size() == 12);
  assert(Serial.output[0] == 245 && Serial.output[1] == 10);
  uint8_t checksum = 0;
  for (int i=2; i<11; ++i) checksum += Serial.output[i];
  assert(checksum == Serial.output[11]);
  uint32_t decodedLeft = 0, decodedRight = 0;
  for (int i=0; i<4; ++i) {
    decodedLeft = (decodedLeft << 8) | Serial.output[3+i];
    decodedRight = (decodedRight << 8) | Serial.output[7+i];
  }
  assert(decodedLeft == left && decodedRight == right);
}
''')
    binary = tmp_path / 'firmware_test'
    subprocess.run([compiler, '-std=c++11', '-I', str(tmp_path),
                    str(source), '-o', str(binary)], check=True)
    subprocess.run([str(binary)], check=True)
