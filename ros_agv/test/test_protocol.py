"""Protocol and differential-drive regression tests without ROS or hardware."""
import struct

from ros_agv.protocol import Decoder, encoder_delta, motor_packet, packet, wheel_commands


def test_motor_wire_format():
    assert motor_packet(-100, 100) == bytes([0xF5, 4, 1, 156, 100, 1])
    assert motor_packet(-999, 999) == motor_packet(-100, 100)


def test_fragmented_and_consecutive_feedback():
    frame = packet(3, struct.pack('>II', 0x80000001, 456))
    assert len(frame) == 12
    decoder = Decoder()
    assert decoder.feed(frame[:5]) == []
    results = decoder.feed(frame[5:] + frame)
    assert len(results) == 2
    assert struct.unpack('>II', results[0][1]) == (0x80000001, 456)


def test_corruption_and_invalid_length_recovery():
    good = packet(3, struct.pack('>II', 1, 2))
    bad = good[:-1] + bytes([good[-1] ^ 1])
    decoder = Decoder()
    assert decoder.feed(b'noise\xf5\xff\x03' + bad + good) == [(3, good[3:-1])]


def test_drive_directions_and_proportional_saturation():
    assert wheel_commands(0.25, 0, 0.4, 0.5) == (50, 50)
    assert wheel_commands(-0.25, 0, 0.4, 0.5) == (-50, -50)
    assert wheel_commands(0, 1, 0.4, 0.5) == (-40, 40)
    assert wheel_commands(0.5, 2.5, 0.4, 0.5) == (0, 100)
    assert wheel_commands(0, 0, 0.4, 0.5) == (0, 0)


def test_encoder_rollover():
    assert encoder_delta(0, 0xFFFFFFFF) == 1
    assert encoder_delta(5, 0xFFFFFFFE) == 7
    assert encoder_delta(110, 100) == 10
    assert encoder_delta(100, 100) == 0
