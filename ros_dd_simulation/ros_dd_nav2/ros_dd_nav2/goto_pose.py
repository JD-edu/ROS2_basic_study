#!/usr/bin/env python3
"""Send repeated map-frame goals to Nav2 from a terminal."""
import math
import os
import select
import sys
import time

from action_msgs.msg import GoalStatus
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import NavigateToPose
import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.signals import SignalHandlerOptions


def parse_goal(line):
    """Parse x y [yaw in degrees], rejecting non-finite coordinates."""
    values = [float(value) for value in line.split()]
    if len(values) not in (2, 3) or not all(math.isfinite(v) for v in values):
        raise ValueError('x y 또는 x y yaw(도)를 입력하세요. 예: 1.0 2.0 90')
    return (*values, 0.0) if len(values) == 2 else tuple(values)


def create_pose_stamped(node, x, y, yaw):
    """Construct a map-frame pose using the node's ROS clock."""
    pose = PoseStamped()
    pose.header.frame_id = 'map'
    pose.header.stamp = node.get_clock().now().to_msg()
    pose.pose.position.x = float(x)
    pose.pose.position.y = float(y)
    angle = math.radians(yaw)
    pose.pose.orientation.z = math.sin(angle / 2)
    pose.pose.orientation.w = math.cos(angle / 2)
    return pose


class GoalTerminal(Node):
    """Keep ROS callbacks running while the user types new goals."""

    def __init__(self):
        super().__init__('goto_pose')
        self.client = ActionClient(self, NavigateToPose, 'navigate_to_pose')
        self.pending = None
        self.goal_handle = None
        self.sending = False
        self.canceling = False
        self.quitting = False
        self.cancel_requested = False
        self.last_feedback = 0.0
        self.timer = self.create_timer(0.1, self.dispatch, clock=rclpy.clock.Clock())

    def submit(self, coordinates):
        self.cancel_requested = False
        self.pending = coordinates
        print(f'[목표 대기] x={coordinates[0]}, y={coordinates[1]}, yaw={coordinates[2]}°',
              flush=True)
        if not self.client.server_is_ready():
            print('[대기] /navigate_to_pose 액션 서버를 기다립니다.', flush=True)

    def dispatch(self):
        if self.goal_handle is not None:
            if (self.pending is not None or self.quitting or self.cancel_requested) and not self.canceling:
                self.canceling = True
                future = self.goal_handle.cancel_goal_async()
                future.add_done_callback(self.cancel_response)
            return
        if self.quitting or self.pending is None or self.sending:
            return
        if not self.client.server_is_ready():
            return
        goal = NavigateToPose.Goal()
        goal.pose = create_pose_stamped(self, *self.pending)
        self.pending = None
        self.sending = True
        future = self.client.send_goal_async(goal, feedback_callback=self.feedback)
        future.add_done_callback(self.accepted)

    def accepted(self, future):
        self.sending = False
        try:
            handle = future.result()
            if not handle.accepted:
                print('[거절] Nav2가 목표를 거절했습니다. 다음 목표를 입력하세요.', flush=True)
                return
            self.goal_handle = handle
            self.canceling = False
            self.last_feedback = 0.0
            print('[이동] 목표가 접수되었습니다.', flush=True)
            handle.get_result_async().add_done_callback(self.finished)
        except Exception as error:
            self.get_logger().error(f'목표 전송 실패: {error}')

    def cancel_response(self, future):
        try:
            if not future.result().goals_canceling:
                self.get_logger().warning('취소 요청이 수락되지 않았습니다. 현재 결과를 기다립니다.')
        except Exception as error:
            self.get_logger().error(f'취소 요청 실패: {error}')

    def feedback(self, message):
        now = time.monotonic()
        if now - self.last_feedback >= 2.0:
            print(f'[이동] 남은 거리: {message.feedback.distance_remaining:.2f} m', flush=True)
            self.last_feedback = now

    def finished(self, future):
        self.goal_handle = None
        self.canceling = False
        self.cancel_requested = False
        try:
            status = future.result().status
            label = {GoalStatus.STATUS_SUCCEEDED: '도착',
                     GoalStatus.STATUS_CANCELED: '취소',
                     GoalStatus.STATUS_ABORTED: '실패'}.get(status, f'상태 {status}')
            print(f'[{label}] 다음 x y를 입력할 수 있습니다.', flush=True)
        except Exception as error:
            self.get_logger().error(f'결과 수신 실패: {error}')

    def stop(self):
        self.quitting = True
        self.pending = None
        self.dispatch()


def main(args=None):
    rclpy.init(args=args, signal_handler_options=SignalHandlerOptions.NO)
    node = GoalTerminal()
    print('지도 좌표 입력: x y [yaw(도)]  |  cancel: 이동 취소  |  q: 종료', flush=True)
    print('yaw 생략 시 0도. 이동 중 새 목표를 입력하면 기존 목표를 취소하고 이동합니다.', flush=True)
    buffered = ''
    lines = []
    try:
        while rclpy.ok() and not node.quitting:
            rclpy.spin_once(node, timeout_sec=0.05)
            if not lines and select.select([sys.stdin], [], [], 0)[0]:
                chunk = os.read(sys.stdin.fileno(), 4096)
                if chunk:
                    buffered += chunk.decode('utf-8', errors='replace')
                    complete = buffered.split('\n')
                    lines.extend(complete[:-1])
                    buffered = complete[-1]
                else:
                    if buffered:
                        lines.append(buffered)
                        buffered = ''
                    lines.append('q')
            if not lines:
                continue
            line = lines.pop(0)
            if line.strip().lower() in ('q', 'quit', 'exit'):
                node.stop()
            elif line.strip().lower() == 'cancel':
                node.pending = None
                node.cancel_requested = True
                if node.goal_handle is not None and not node.canceling:
                    node.canceling = True
                    node.goal_handle.cancel_goal_async().add_done_callback(node.cancel_response)
            elif line.strip():
                try:
                    node.submit(parse_goal(line))
                except ValueError as error:
                    print(f'[입력 오류] {error}', flush=True)
    except KeyboardInterrupt:
        node.stop()
    finally:
        node.stop()
        deadline = time.monotonic() + 3.0
        try:
            while rclpy.ok() and (node.sending or node.goal_handle is not None):
                if time.monotonic() >= deadline:
                    node.get_logger().warning('종료 전 목표 취소 확인 시간이 초과되었습니다.')
                    break
                rclpy.spin_once(node, timeout_sec=0.1)
        except KeyboardInterrupt:
            pass
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
