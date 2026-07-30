import pybullet as p
import pybullet_data
import time

# 1. PyBullet GUI 모드 실행
physicsClient = p.connect(p.GUI)

# 2. 카메라 시점 설정
p.resetDebugVisualizerCamera(cameraDistance=2.5, cameraYaw=45, cameraPitch=-30, cameraTargetPosition=[0, 0, 0.3])

# 3. 기본 데이터 경로 추가 및 바닥 생성
p.setAdditionalSearchPath(pybullet_data.getDataPath())
planeId = p.loadURDF("plane.urdf")

# 4. URDF 로드 (★ 핵심 해결책!)
# useFixedBase=True : 로봇을 공중에 완전히 고정시켜 바닥 아래로 떨어지거나 빠지지 않게 만듭니다.
# [0, 0, 0.3] : Z축 높이를 0.3m 위로 띄워서 바닥 평면과 겹치지 않게 배치합니다.
robotId = p.loadURDF("ros_dd.urdf", basePosition=[0, 0, 0.3], useFixedBase=True)

# 5. 로봇 조인트(관절) 정보 출력
num_joints = p.getNumJoints(robotId)
print(f"--- 로봇 조인트 개수: {num_joints} ---")
for i in range(num_joints):
    joint_info = p.getJointInfo(robotId, i)
    print(f"Joint [{i}]: {joint_info[1].decode('utf-8')}")

print("\n[안내] 로봇이 공중에 고정되었습니다. 마우스 드래그로 조작해 보세요.")

# 6. GUI 시뮬레이션 유지
try:
    while True:
        p.stepSimulation()
        time.sleep(1.0 / 240.0)
except KeyboardInterrupt:
    p.disconnect()