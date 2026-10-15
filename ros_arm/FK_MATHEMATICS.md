# ros_arm 순기구학(FK)의 수학과 구현

## 1. 목적과 현재 구현 범위

순기구학(Forward Kinematics, FK)은 관절각 벡터

\[
\mathbf q = [q_1, q_2, q_3, q_4]^T
\]

가 주어졌을 때 각 링크의 자세와 말단 위치를 계산하는 문제다. 현재 구현은
[`ros_arm/mujoco_fk.py`](ros_arm/mujoco_fk.py)에서 관절각을 키보드로 바꾸고,
MuJoCo의 `mj_forward`가 MJCF 트리에 정의된 변환을 전파하도록 한다.

이 예제는 actuator의 토크로 움직이는 동역학 시뮬레이션이 아니다. `qpos`를
직접 갱신하고 `mj_forward`를 호출하는 **kinematic visualization**이다. 따라서
질량, 관성, 중력, 접촉력은 FK 결과에 관여하지 않는다.

## 2. 좌표계와 관절 순서

코드에서 사용하는 관절 순서는 다음과 같다.

| 번호 | 관절 이름 | 부모 → 자식 | 축 | 범위 |
|---:|---|---|---|---|
| 1 | `base_shoulder` | base → shoulder | 로컬 Z | \([-\pi,\pi]\) |
| 2 | `shoulder_arm1` | shoulder → arm 1 | 로컬 Z | \([-\pi,\pi]\) |
| 3 | `arm1_arm2` | arm 1 → arm 2 | 로컬 Z | \([-\pi,\pi]\) |
| 4 | `arn2_end_arm` | arm 2 → end arm | 로컬 Z | \([-\pi,\pi]\) |

모든 관절은 revolute joint다. 여기서 “로컬 Z축”은 월드 Z축과 항상 같다는
뜻이 아니다. 앞선 고정 회전에 의해 각 관절축의 월드 방향이 달라진다.

초기 자세는 다음과 같다.

\[
\mathbf q_{home}
= [0^\circ,-35^\circ,70^\circ,-35^\circ]^T.
\]

이 자세는 일직선으로 펴진 특이 자세를 피하고 FK와 IK를 관찰하기 쉽도록
정한 시연용 자세다.

## 3. 동차변환 행렬

회전행렬 \(R\in SO(3)\)와 위치 \(\mathbf p\in\mathbb R^3\)를 하나의
4×4 동차변환으로 표현하면 다음과 같다.

\[
T =
\begin{bmatrix}
R & \mathbf p\\
\mathbf 0^T & 1
\end{bmatrix}.
\]

점 \(\mathbf x\)를 동차좌표 \(\bar{\mathbf x}=[x,y,z,1]^T\)로 만들면

\[
\bar{\mathbf x}_{world}=T_{world,link}\bar{\mathbf x}_{link}
\]

로 좌표계를 변환할 수 있다.

평행이동은

\[
\operatorname{Trans}(x,y,z)=
\begin{bmatrix}
1&0&0&x\\
0&1&0&y\\
0&0&1&z\\
0&0&0&1
\end{bmatrix}
\]

이고, 이 로봇의 모든 가동 관절에 사용되는 Z축 회전은

\[
\operatorname{RotZ}(q)=
\begin{bmatrix}
\cos q&-\sin q&0&0\\
\sin q& \cos q&0&0\\
0&0&1&0\\
0&0&0&1
\end{bmatrix}
\]

이다.

URDF의 `rpy="r p y"`는 roll, pitch, yaw를 사용하며 회전행렬은

\[
R_{rpy}=R_z(y)R_y(p)R_x(r)
\]

로 해석한다. 따라서 관절 \(i\)의 부모에서 자식으로 가는 변환은

\[
{}^{i-1}T_i(q_i)
= \operatorname{Trans}(\mathbf t_i)
  \operatorname{RotRPY}(\mathbf r_i)
  \operatorname{RotZ}(q_i)
\]

이다. 고정 origin 변환을 먼저 적용하고, 그 결과로 만들어진 관절 좌표계의
Z축을 중심으로 \(q_i\)만큼 회전한다.

## 4. ros_arm의 실제 변환 체인

URDF에서 읽은 고정 origin은 다음과 같다. 길이 단위는 m, 각도 단위는 rad다.

\[
\mathbf t_1 =
\begin{bmatrix}0.0003\\0\\0.03815\end{bmatrix},\quad
\mathbf r_1 =
\begin{bmatrix}\pi\\0\\0\end{bmatrix}
\]

\[
\mathbf t_2 =
\begin{bmatrix}-5.94002\times10^{-6}\\-0.00408879\\-0.03095\end{bmatrix},
\quad
\mathbf r_2 =
\begin{bmatrix}\pi/2\\-\pi/2\\0\end{bmatrix}
\]

\[
\mathbf t_3 =
\begin{bmatrix}-0.07515\\0\\0.0000500002\end{bmatrix},\quad
\mathbf r_3=\mathbf 0
\]

\[
\mathbf t_4 =
\begin{bmatrix}-0.07515\\0\\0.0000500002\end{bmatrix},\quad
\mathbf r_4=\mathbf 0.
\]

각 변환을 \(A_i(q_i)={} ^{i-1}T_i(q_i)\)라고 정의하면 말단 body의
월드 변환은

\[
{}^0T_4(\mathbf q)
=A_1(q_1)A_2(q_2)A_3(q_3)A_4(q_4)
\]

이다. 행렬 곱의 순서는 바꿀 수 없다. 회전과 평행이동은 일반적으로
교환법칙을 만족하지 않기 때문이다.

말단 body의 로컬 \(-X\) 방향 0.03 m 위치에 `tcp_site`를 두었으므로

\[
\bar{\mathbf p}_{TCP}
= {}^0T_4(\mathbf q)
\begin{bmatrix}-0.03\\0\\0\\1\end{bmatrix}
\]

이고, 결과 벡터의 앞 세 성분이 월드 XYZ다.

### J4와 현재 TCP 정의의 중요한 관계

`tcp_site`는 J4 축에서 0.03 m 떨어져 있다. 따라서 J4가 회전하면 site가
반지름 0.03 m인 원호를 따라 움직이며 TCP 위치가 변한다.

로컬 TCP 위치를 \(\mathbf r=[-0.03,0,0]^T\)라고 하면

\[
R_z(q_4)\mathbf r
=\begin{bmatrix}
-0.03\cos q_4\\
-0.03\sin q_4\\
0
\end{bmatrix}
\]

이므로 일반적으로

\[
\frac{\partial \mathbf p_{TCP}}{\partial q_4}\ne\mathbf 0
\]

이다. 뷰어에는 이 위치가 반지름 0.003 m의 밝은 녹색 구형 marker로 표시된다.

## 5. 기하학적 위치 Jacobian과 FK의 관계

revolute joint \(i\)의 월드 축을 \(\mathbf z_i\), 축 위의 한 점을
\(\mathbf o_i\), TCP 위치를 \(\mathbf p\)라고 하면 위치 Jacobian의 열은

\[
J_{p,i}=\mathbf z_i\times(\mathbf p-\mathbf o_i)
\]

이다. 따라서

\[
\dot{\mathbf p}=J_p(\mathbf q)\dot{\mathbf q}.
\]

이 식은 IK 문서에서 관절 변화가 TCP 위치를 얼마나 움직이는지 계산할 때
사용한다. 현재 J4에서 TCP까지 거리가 0.03 m이므로 네 번째 Jacobian 열도
위치 IK에 기여한다.

## 6. 코드에서 FK가 수행되는 과정

키를 한 번 누르면 해당 목표 관절각이 5° 변한다. 관절 한계는
`model.jnt_range`로 clipping한다.

렌더 루프에서는 목표각으로 즉시 점프하지 않고

\[
\mathbf q_{k+1}
=\mathbf q_k+0.18(\mathbf q_{target}-\mathbf q_k)
\]

를 적용한다. 이것은 물리적 속도 제어기가 아니라 화면에서 부드럽게 보이게
하는 1차 지수 보간이다. 오차는 매 프레임 \(0.82\)배가 되므로

\[
\mathbf e_k=0.82^k\mathbf e_0
\]

로 감소한다.

그 뒤 다음 순서가 실행된다.

1. `data.qpos`에 새 관절각을 기록한다.
2. `data.qvel`을 0으로 둔다.
3. `mujoco.mj_forward(model, data)`를 호출한다.
4. MuJoCo가 body tree를 따라 모든 \(T\)를 곱한다.
5. `data.site_xpos[tip_id]`에서 TCP 월드 위치를 읽는다.
6. GLFW renderer가 갱신된 body 자세를 그린다.

MuJoCo의 `mj_forward`를 사용하므로 별도의 DH 파라미터 체인을 중복 작성하지
않고 MJCF에 변환된 URDF 좌표계를 그대로 사용한다.

## 7. 키 매핑

| 관절 | 증가 | 감소 |
|---|---:|---:|
| J1 | `1` | `Q` |
| J2 | `2` | `W` |
| J3 | `3` | `E` |
| J4 | `4` | `R` |

`0`은 home 자세, `Esc`는 종료다.

```bash
python3 -m ros_arm.mujoco_fk
```
