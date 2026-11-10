"""Tkinter lidar viewer with ROS2, direct serial and standalone demo modes."""

import argparse
import math
import time
import tkinter as tk

from diy_lidar.protocol import SerialScans


def demo_ranges(seconds):
    """Simulate the same room and moving obstacle as the Arduino sketch."""
    ranges = []
    cx, cy, radius = 1.5, 0.8 * math.sin(seconds * 0.6), 0.4
    for degree in range(360):
        angle = math.radians(degree)
        dx, dy = math.cos(angle), math.sin(angle)
        distance = min(3 / max(abs(dx), 1e-9), 3 / max(abs(dy), 1e-9))
        projection = cx * dx + cy * dy
        disc = projection ** 2 - (cx ** 2 + cy ** 2 - radius ** 2)
        if disc >= 0:
            hit = projection - math.sqrt(disc)
            if hit > 0:
                distance = min(distance, hit)
        ranges.append(distance)
    return ranges


class LidarViewer:
    """Poll input and draw scans exclusively on Tk's event thread."""

    def __init__(self, args):
        self.args = args
        self.source = None
        self.node = None
        self.ros = None
        self.latest = None
        self.received = None
        self.started = time.monotonic()
        if args.mode == 'serial':
            self.source = SerialScans(args.port, args.baud)
        elif args.mode == 'ros':
            import rclpy
            from rclpy.qos import qos_profile_sensor_data
            from sensor_msgs.msg import LaserScan
            self.ros = rclpy
            rclpy.init()
            self.node = rclpy.create_node('lidar_viewer')
            self.node.create_subscription(
                LaserScan, args.topic, self.on_scan, qos_profile_sensor_data)
        self.root = tk.Tk()
        self.root.title(f'DIY Lidar — {args.mode}')
        self.canvas = tk.Canvas(self.root, width=700, height=700, bg='#101923')
        self.canvas.pack(fill=tk.BOTH, expand=True)
        self.status = tk.Label(self.root, text='Waiting for scan...')
        self.status.pack()
        self.root.protocol('WM_DELETE_WINDOW', self.close)
        self.root.after(30, self.tick)

    def on_scan(self, msg):
        """Store a ROS scan, including its original angular geometry."""
        self.latest = (msg.ranges, msg.angle_min, msg.angle_increment)
        self.received = time.monotonic()

    def tick(self):
        """Poll input without blocking the GUI."""
        try:
            if self.args.mode == 'demo':
                self.latest = (demo_ranges(time.monotonic() - self.started),
                               0.0, math.tau / 360)
                self.received = time.monotonic()
            elif self.source is not None:
                scan = self.source.poll()
                if scan is not None:
                    self.latest = (scan[1], 0.0, math.tau / 360)
                    self.received = time.monotonic()
            else:
                self.ros.spin_once(self.node, timeout_sec=0.0)
        except (OSError, RuntimeError) as exc:
            self.status.config(text=f'Input error: {exc}. Restart the viewer.')
            return
        self.draw()
        self.root.after(30, self.tick)

    def draw(self):
        """Draw range rings and lidar points: forward up, left to the left."""
        canvas = self.canvas
        canvas.delete('all')
        width, height = canvas.winfo_width(), canvas.winfo_height()
        x0, y0 = width / 2, height / 2
        scale = max(1, min(width, height) / 2 - 35) / self.args.max_range
        for metre in range(1, math.ceil(self.args.max_range) + 1):
            radius = metre * scale
            canvas.create_oval(x0 - radius, y0 - radius, x0 + radius,
                               y0 + radius, outline='#334556')
            canvas.create_text(x0 + 8, y0 - radius + 10,
                               text=f'{metre} m', fill='#9bafbd', anchor='w')
        canvas.create_line(x0, 20, x0, height - 20, fill='#334556')
        canvas.create_line(20, y0, width - 20, y0, fill='#334556')
        canvas.create_text(x0, 12, text='FRONT (+X)', fill='white')
        canvas.create_text(48, y0 - 12, text='LEFT (+Y)', fill='white')
        canvas.create_polygon(x0, y0 - 9, x0 - 6, y0 + 6, x0 + 6,
                              y0 + 6, fill='#ffbd69')
        if self.latest is None:
            return
        ranges, start, step = self.latest
        for index, distance in enumerate(ranges):
            if not math.isfinite(distance) or not 0 < distance <= self.args.max_range:
                continue
            angle = start + index * step
            x = x0 - distance * math.sin(angle) * scale
            y = y0 - distance * math.cos(angle) * scale
            canvas.create_oval(x - 2, y - 2, x + 2, y + 2,
                               fill='#51ebbe', outline='')
        age = time.monotonic() - self.received
        state = 'STALE' if age > 1.0 else 'Receiving'
        self.status.config(text=f'{state} | {len(ranges)} points | '
                           f'last scan {age:.1f}s ago | {self.args.mode}')

    def close(self):
        """Release serial / ROS resources and close the window."""
        if self.source is not None:
            self.source.close()
        if self.node is not None:
            self.node.destroy_node()
        if self.ros is not None and self.ros.ok():
            self.ros.shutdown()
        self.root.destroy()


def main():
    """Start the selected viewer mode."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--mode', choices=['ros', 'serial', 'demo'], default='ros')
    parser.add_argument('--port', default='/dev/ttyACM0')
    parser.add_argument('--baud', type=int, default=115200)
    parser.add_argument('--topic', default='/scan')
    parser.add_argument('--max-range', type=float, default=5.0)
    args = parser.parse_args()
    if not math.isfinite(args.max_range) or not 0.1 <= args.max_range <= 100:
        parser.error('--max-range must be between 0.1 and 100 metres')
    viewer = LidarViewer(args)
    try:
        viewer.root.mainloop()
    except KeyboardInterrupt:
        viewer.close()


if __name__ == '__main__':
    main()
