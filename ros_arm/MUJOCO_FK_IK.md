# ros_arm MuJoCo FK / IK 프로토타입

URDF에서 변환한 `mjcf/jdcobot10.xml`과 `meshes/`를 사용하는 4축 로봇암
예제입니다. `mjcf/scene.xml`이 로봇 XML을 include하고, jdCobot200 예제의
조명, gradient skybox, checker 바닥 구성을 제공합니다.
URDF에 actuator가 없으므로 두 예제 모두 관절 좌표를 직접 갱신하는 kinematic
시각화입니다. 렌더링은 `mujoco.viewer`가 아닌 GLFW 창과 MuJoCo 렌더링
컨텍스트를 직접 생성하는 방식입니다.

## 의존성

```bash
python3 -m pip install mujoco numpy glfw
```

## FK: 관절 공간 키 조작

```bash
python3 -m ros_arm.mujoco_fk
```

| 관절 | 증가 | 감소 |
|---|---:|---:|
| J1 `base_shoulder` | `1` | `Q` |
| J2 `shoulder_arm1` | `2` | `W` |
| J3 `arm1_arm2` | `3` | `E` |
| J4 `arn2_end_arm` | `4` | `R` |

한 번 누를 때 5도씩 목표 관절각이 변합니다. `0`은 home, `Esc`는 종료입니다.
터미널에는 FK로 얻은 말단 body의 xyz 좌표가 표시됩니다.

뷰어 카메라는 마우스 왼쪽 버튼으로 회전하고, 오른쪽 버튼으로 이동하며,
가운데 버튼 또는 휠로 확대/축소할 수 있습니다.

## IK: Cartesian 키 조작

```bash
python3 -m ros_arm.mujoco_ik
```

| Cartesian 축 | 증가 | 감소 |
|---|---:|---:|
| X | `W` | `S` |
| Y | `A` | `D` |
| Z | `R` | `F` |

한 번 누를 때 목표가 5 mm 이동합니다. `0`은 home 자세와 현재 목표를 함께
초기화하고, `Esc`는 종료합니다. IK는 과거 jdCobot200 코드와 같은 MuJoCo
위치 Jacobian 기반 Damped Least Squares 수치 IK입니다.

TCP는 마지막 관절축에서 로컬 `-X` 방향으로 0.03 m 떨어진 `tcp_site`이며,
뷰어에서 반지름 3 mm의 밝은 녹색 구로 표시됩니다.

요청한 프로토타입 범위에 따라 바닥 충돌, self-collision, 경로 사전 검사는
구현하지 않았습니다. 관절 한계와 속도 한계만 solver에 적용됩니다.
