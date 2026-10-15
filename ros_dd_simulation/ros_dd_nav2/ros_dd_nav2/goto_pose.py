#!/usr/bin/env python3
"""터미널 입력과 NavigateToPose Action 콜백으로 목표를 전달합니다."""

import math
import queue
import threading
import time

import rclpy
from action_msgs.msg import GoalStatus
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import NavigateToPose
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.signals import SignalHandlerOptions


def create_pose_stamped(node: Node, x: float, y: float, yaw: float) -> PoseStamped:
    pose = PoseStamped()
    pose.header.frame_id = 'map'
    pose.header.stamp = node.get_clock().now().to_msg()
    pose.pose.position.x = x
    pose.pose.position.y = y
    yaw_rad = math.radians(yaw)
    pose.pose.orientation.z = math.sin(yaw_rad / 2.0)
    pose.pose.orientation.w = math.cos(yaw_rad / 2.0)
    return pose


class GotoPose(Node):
    """Action 상태는 Executor 스레드에서만 변경합니다."""

    def __init__(self):
        super().__init__('goto_pose')
        self.client = ActionClient(self, NavigateToPose, 'navigate_to_pose')
        self.commands = queue.Queue()
        self.command_guard = self.create_guard_condition(self.process_commands)
        self.stopped = threading.Event()
        self.busy = False
        self.goal_handle = None
        self.exiting = False
        self.exit_timer = None
        self.last_feedback = 0.0

    def read_commands(self):
        # 입력 스레드는 ROS API나 Action 상태에 접근하지 않습니다.
        while not self.stopped.is_set():
            try:
                command = input('목표 입력> ').strip()
            except EOFError:
                command = 'quit'
            if self.stopped.is_set():
                return
            self.commands.put(command)
            self.command_guard.trigger()
            if command.lower() in ('q', 'quit', 'exit'):
                return

    def process_commands(self):
        while not self.commands.empty() and not self.exiting:
            command = self.commands.get_nowait()
            if command.lower() in ('q', 'quit', 'exit'):
                self.request_exit()
                return
            if not command:
                continue
            try:
                values = command.split()
                if len(values) != 3:
                    raise ValueError
                x, y, yaw = map(float, values)
                if not all(math.isfinite(value) for value in (x, y, yaw)):
                    raise ValueError
            except ValueError:
                print('[WARN] 유한한 숫자 3개를 입력하세요. 예: 2.0 3.0 90')
                continue
            if self.busy:
                print('[WARN] 이동 중입니다. 완료 후 목표를 다시 입력하세요.')
                continue
            goal = NavigateToPose.Goal()
            goal.pose = create_pose_stamped(self, x, y, yaw)
            self.busy = True
            self.last_feedback = time.monotonic()
            print(f'[INFO] 목표 요청: x={x}, y={y}, yaw={yaw}도')
            try:
                future = self.client.send_goal_async(
                    goal, feedback_callback=self.on_feedback)
                future.add_done_callback(self.on_goal_response)
            except Exception as error:
                self.task_finished(f'[ERROR] 목표 전송 실패: {error}')

    def on_goal_response(self, future):
        try:
            self.goal_handle = future.result()
            if not self.goal_handle.accepted:
                self.task_finished('[ERROR] 목표가 거부되었습니다.')
                return
            print('[INFO] 목표가 수락되었습니다.')
            result_future = self.goal_handle.get_result_async()
            result_future.add_done_callback(self.on_result)
            # 목표 수락 응답을 기다리는 동안 종료가 요청될 수도 있습니다.
            if self.exiting:
                self.cancel_goal()
        except Exception as error:
            self.task_finished(f'[ERROR] 목표 응답 처리 실패: {error}')

    def on_feedback(self, message):
        if time.monotonic() - self.last_feedback >= 1.0:
            distance = message.feedback.distance_remaining
            print(f'[INFO] 남은 거리: {distance:.2f}m')
            self.last_feedback = time.monotonic()

    def on_result(self, future):
        try:
            status = future.result().status
            messages = {
                GoalStatus.STATUS_SUCCEEDED: '[SUCCESS] 목표 지점에 도달했습니다!',
                GoalStatus.STATUS_CANCELED: '[WARN] 이동 명령이 취소되었습니다.',
                GoalStatus.STATUS_ABORTED: '[ERROR] 목표 지점 이동에 실패했습니다.',
            }
            self.task_finished(messages.get(status, f'[WARN] 이동 종료 상태: {status}'))
        except Exception as error:
            self.task_finished(f'[ERROR] 결과 수신 실패: {error}')

    def task_finished(self, message):
        self.busy = False
        self.goal_handle = None
        print(message)
        if self.exiting:
            self.finish_exit()
        else:
            print('[INFO] 다음 목표를 입력하세요.')

    def request_exit(self):
        if self.exiting:
            return
        self.exiting = True
        self.stopped.set()
        if not self.busy:
            self.finish_exit()
            return
        print('[INFO] 이동 취소 및 종료를 요청합니다...')
        # 시뮬레이션이 일시 정지되어도 종료 제한 시간은 진행됩니다.
        from rclpy.clock import Clock, ClockType
        self.exit_timer = self.create_timer(
            5.0, self.on_exit_timeout, clock=Clock(clock_type=ClockType.STEADY_TIME))
        if self.goal_handle is not None:
            self.cancel_goal()

    def cancel_goal(self):
        try:
            future = self.goal_handle.cancel_goal_async()
            future.add_done_callback(self.on_cancel_response)
        except Exception as error:
            print(f'[WARN] 취소 요청 실패: {error}')

    def on_cancel_response(self, future):
        try:
            if not future.result().goals_canceling:
                print('[WARN] 취소가 수락되지 않았습니다. 최종 결과를 기다립니다.')
        except Exception as error:
            print(f'[WARN] 취소 응답 수신 실패: {error}')

    def on_exit_timeout(self):
        print('[WARN] 5초 내 종료 결과를 받지 못했습니다. 로봇 정지 여부를 확인하세요.')
        self.finish_exit()

    def finish_exit(self):
        self.stopped.set()
        rclpy.try_shutdown()


def main():
    rclpy.init(signal_handler_options=SignalHandlerOptions.NO)
    node = GotoPose()
    try:
        print('[INFO] navigate_to_pose Action 서버를 기다립니다...')
        while rclpy.ok() and not node.client.wait_for_server(timeout_sec=1.0):
            pass
        if rclpy.ok():
            print('목표: x y yaw (m, m, 도). 예: 2.0 3.0 90')
            print('이동 완료 후 다음 목표를 입력하세요. 종료: q / quit / exit / Ctrl+C')
            threading.Thread(target=node.read_commands, daemon=True).start()
            try:
                rclpy.spin(node)
            except KeyboardInterrupt:
                node.request_exit()
                if rclpy.ok():
                    rclpy.spin(node)
    except KeyboardInterrupt:
        print('\n[INFO] 프로그램을 종료합니다.')
    finally:
        node.stopped.set()
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
