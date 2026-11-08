"""Two-wheel packets: F5, body length, command, payload, additive checksum."""
import struct

HEAD = 0xF5
CMD_MOTOR = 0x01
CMD_ENCODER = 0x03
PAYLOAD_LENGTHS = {CMD_MOTOR: 2, CMD_ENCODER: 8}


def packet(command, payload):
    """Length includes command, payload and checksum; checksum excludes header/length."""
    body = bytes([command]) + payload
    return bytes([HEAD, len(body) + 1]) + body + bytes([sum(body) & 255])


def motor_packet(left, right):
    """Encode signed percent commands."""
    return packet(CMD_MOTOR, struct.pack('bb', *[
        max(-100, min(100, int(v))) for v in (left, right)]))


def wheel_commands(linear, angular, separation, maximum):
    """Limit both wheels together to preserve the turning radius."""
    left = linear - angular * separation / 2
    right = linear + angular * separation / 2
    scale = 100 / max(maximum, abs(left), abs(right))
    return round(left * scale), round(right * scale)


def encoder_delta(current, previous):
    """Handle signed 32-bit counter rollover."""
    return (current - previous + (1 << 31)) % (1 << 32) - (1 << 31)


class Decoder:
    """Buffer fragmented packets and recover from corrupt frames."""

    def __init__(self):
        self.buffer = bytearray()

    def feed(self, data):
        """Return validated command/payload pairs."""
        self.buffer.extend(data)
        result = []
        while self.buffer:
            if self.buffer[0] != HEAD:
                del self.buffer[0]
                continue
            if len(self.buffer) < 3:
                break
            length, command = self.buffer[1:3]
            if length != PAYLOAD_LENGTHS.get(command, -100) + 2:
                del self.buffer[0]
                continue
            total = length + 2
            if len(self.buffer) < total:
                break
            body = self.buffer[2:total]
            if (sum(body[:-1]) & 255) != body[-1]:
                del self.buffer[0]
                continue
            result.append((command, bytes(body[1:-1])))
            del self.buffer[:total]
        return result
