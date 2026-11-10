'''
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
'''

import time
import serial

# -----------------------------------------------------------------------------
# ROS 2 노드 -> 아두이노 모터 제어 프로토콜
# 단독 PC 테스트도 같은 패킷을 사용합니다. 통신: USB Serial, 115200 baud, 8N1.
# ROS의 cmd_vel(Twist)은 Python에서 좌우 속도로 변환하며, 아두이노에는
# Twist 자체가 아닌 아래의 6바이트 이진 패킷을 보냅니다.
#
# 바이트 위치  의미          값
#     0       헤더          0xF5 (패킷 시작)
#     1       길이          0x04 (명령 1 + 좌우 속도 2 + 체크섬 1)
#     2       명령          0x01 (좌우 모터 제어)
#     3       왼쪽 속도     signed int8, -100~100
#     4       오른쪽 속도   signed int8, -100~100
#     5       체크섬        (명령 + 왼쪽 속도 바이트 + 오른쪽 속도 바이트) & 0xFF
#
# 속도는 m/s가 아닌 모터 출력 명령입니다. 양수=전진, 음수=후진, 0=정지.
# 음수는 2의 보수로 전송합니다. 예: -20 & 0xFF = 236 = 0xEC.
# 체크섬 계산에는 헤더와 길이를 포함하지 않습니다.
# 예: 좌우 20, 20 -> F5 04 01 14 14 29 (모두 16진수)
# 예: 좌우 -20, 20 -> F5 04 01 EC 14 01 (모두 16진수)
# 예: 정지 0, 0 -> F5 04 01 00 00 01 (모두 16진수)
# 아두이노는 유효한 모터 명령을 500ms 동안 받지 못하면 자동 정지합니다.
# -----------------------------------------------------------------------------

# 여기만 수정하세요. 속도: -100(후진) ~ 0(정지) ~ 100(전진)
PORT = "/dev/ttyUSB0"
LEFT_SPEED = 0
RIGHT_SPEED = 0
RUN_SECONDS = 5


def send_motor(ser, left, right):
    """좌우 속도를 6바이트 패킷으로 보냅니다."""
    if not (-100 <= left <= 100 and -100 <= right <= 100):
        raise ValueError("모터 속도는 -100~100이어야 합니다.")

    # 음수 속도도 한 바이트(0~255)로 표현합니다.
    left_byte = left & 0xFF
    right_byte = right & 0xFF
    checksum = (0x01 + left_byte + right_byte) & 0xFF
    packet = bytes([0xF5, 4, 0x01, left_byte, right_byte, checksum])
    ser.write(packet)


def read_encoder(ser):
    """12바이트가 모이면 좌우 누적 펄스를 읽습니다."""
    if ser.in_waiting < 12:
        return None

    # 헤더를 찾고, 나머지 11바이트를 읽습니다.
    if ser.read(1) != b"\xf5":
        return None
    data = ser.read(11)
    if len(data) != 11:
        return None
    if data[0] != 10 or data[1] != 0x03:
        return None
    if (sum(data[1:10]) & 0xFF) != data[10]:
        return None

    # 방향 정보가 없는 양수 누적 카운터입니다.
    left = int.from_bytes(data[2:6], byteorder="big")
    right = int.from_bytes(data[6:10], byteorder="big")
    return left, right


def main():
    ser = serial.Serial(PORT, 115200, timeout=0.1, write_timeout=0.1)
    try:
        time.sleep(2)  # USB 연결 후 아두이노가 재시작할 시간을 줍니다.
        ser.reset_input_buffer()
        send_motor(ser, 0, 0)
        start = time.monotonic()
        last_feedback = start - 1

        while time.monotonic() - start < RUN_SECONDS:
            # 1. 엔코더를 읽고 출력합니다.
            counts = read_encoder(ser)
            if counts is not None:
                left, right = counts
                print(f"왼쪽 펄스: {left}, 오른쪽 펄스: {right}", flush=True)
                last_feedback = time.monotonic()

            # 2. 피드백이 정상일 때만 설정한 속도를 보냅니다.
            if time.monotonic() - last_feedback < 0.5:
                send_motor(ser, LEFT_SPEED, RIGHT_SPEED)
            else:
                send_motor(ser, 0, 0)

            time.sleep(0.05)  # 0.05초마다 명령을 반복해서 보냅니다.

    except KeyboardInterrupt:
        print("테스트를 중단합니다.")
    finally:
        # 실행 시간이 끝나거나 Ctrl+C를 누르면 정지하고 포트를 닫습니다.
        try:
            send_motor(ser, 0, 0)
        finally:
            ser.close()


if __name__ == "__main__":
    main()
