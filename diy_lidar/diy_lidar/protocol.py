"""Shared serial protocol: SCAN,period_ms,360 integer millimetre ranges."""

import math

SAMPLE_COUNT = 360
RANGE_MIN = 0.05
RANGE_MAX = 8.0


def parse_scan(line):
    """Return (period_seconds, ranges_metres), rejecting malformed frames."""
    fields = line.strip().split(',')
    if len(fields) != SAMPLE_COUNT + 2 or fields[0] != 'SCAN':
        raise ValueError('Expected SCAN,period_ms and 360 distances')
    period_ms = int(fields[1])
    distances = [int(value) for value in fields[2:]]
    if not 1 <= period_ms <= 60000 or any(d < 0 or d > 65535 for d in distances):
        raise ValueError('Invalid period or distance')
    return period_ms / 1000.0, [
        d / 1000.0 if RANGE_MIN <= d / 1000.0 <= RANGE_MAX else math.inf
        for d in distances
    ]


class SerialScans:
    """Read available bytes without blocking and keep incomplete frames."""

    def __init__(self, port, baud):
        import serial
        self.serial = serial.Serial(port, baud, timeout=0)
        self.buffer = b''

    def poll(self):
        """Return the latest complete valid frame, if available."""
        self.buffer += self.serial.read(min(self.serial.in_waiting, 16384))
        latest = None
        while b'\n' in self.buffer:
            line, self.buffer = self.buffer.split(b'\n', 1)
            try:
                latest = parse_scan(line.decode('ascii'))
            except (ValueError, UnicodeDecodeError):
                continue
        if len(self.buffer) > 8192:
            self.buffer = b''
        return latest

    def close(self):
        """Release the serial device."""
        self.serial.close()
