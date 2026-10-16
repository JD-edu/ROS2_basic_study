#!/usr/bin/env python3
import math
import rclpy
from geometry_msgs.msg import PoseStamped
from nav2_simple_commander.robot_navigator import BasicNavigator, TaskResult

def create_pose_stamped(navigator: BasicNavigator, x: float, y: float, yaw: float) -> PoseStamped:
    pose = PoseStamped()
    pose.header.frame_id = 'map'
    # navigator.get_clock() 대신 Node의 현재 시각 사용
    pose.header.stamp = navigator.get_clock().now().to_msg()

    pose.pose.position.x = x
    pose.pose.position.y = y
    pose.pose.position.z = 0.0

    # yaw(도) -> Quaternion 변환
    yaw_rad = math.radians(yaw)
    pose.pose.orientation.x = 0.0
    pose.pose.orientation.y = 0.0
    pose.pose.orientation.z = math.sin(yaw_rad / 2.0)
    pose.pose.orientation.w = math.cos(yaw_rad / 2.0)

    return pose

def main():
    rclpy.init()

    navigator = BasicNavigator()

    # -------------------------------------------------------------
    # IMPORTANT: Initial Pose를 별도로 설정(setInitialPose)하지 않고,
    # Nav2 스택이 이미 활성화되어 있는지만 체크합니다.
    # -------------------------------------------------------------
    print("[INFO] Nav2 활성화 상태를 확인합니다...")
    
    # Cartographer SLAM이나 AMCL이 이미 동작 중이므로 autostart=False 계열 모드로 대기
    navigator.waitUntilNav2Active()
    print("[INFO] Nav2 활성화 완료.")

    # 목표 지점 생성 (x=2.0, y=3.0, yaw=90.0도)
    goal_pose = create_pose_stamped(navigator, x=2.0, y=3.0, yaw=90.0)

    print("[INFO] 목표 지점으로 이동을 요청합니다...")
    navigator.goToPose(goal_pose)

    # 주기적 피드백 확인 Loop
    i = 0
    while not navigator.isTaskComplete():
        i += 1
        feedback = navigator.getFeedback()
        if feedback and i % 5 == 0:
            print(f"[INFO] 남은 거리: {feedback.distance_remaining:.2f}m")
        
        # CPU 점유율 과다 방지를 위해 spin_once 실행
        rclpy.spin_once(navigator, timeout_sec=0.1)

    # 최종 결과 판단
    result = navigator.getResult()
    if result == TaskResult.SUCCEEDED:
        print("[SUCCESS] 목표 지점에 성공적으로 도달했습니다!")
    elif result == TaskResult.CANCELED:
        print("[WARN] 이동 명령이 취소되었습니다.")
    elif result == TaskResult.FAILED:
        print("[ERROR] 목표 지점 이동에 실패했습니다.")

    navigator.lifecycleShutdown()
    rclpy.shutdown()

if __name__ == '__main__':
    main()