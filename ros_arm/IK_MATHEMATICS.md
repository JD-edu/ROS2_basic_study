# ros_arm Jacobian Damped Least Squares IK의 수학과 구현

## 1. 사용한 IK 방식

현재 [`ros_arm/mujoco_ik.py`](ros_arm/mujoco_ik.py)는 Mink를 사용하지 않는다.
과거 jdCobot200의 `numerical_ik` 코드와 같은 **MuJoCo 위치 Jacobian 기반
Damped Least Squares(DLS)** 반복법을 사용한다.

목표는 원하는 월드 위치 \(\mathbf p_d\in\mathbb R^3\)에 TCP를 보내는
관절각 \(\mathbf q\in\mathbb R^4\)를 찾는 것이다.

\[
\mathbf p(\mathbf q)=\mathbf p_d
\]

이 로봇의 FK는 삼각함수가 포함된 비선형 함수이므로 한 번의 선형 계산으로
일반적인 해를 얻지 않고, 현재 자세 주변에서 선형화한 뒤 반복해서 갱신한다.

## 2. 위치 오차

현재 TCP 위치는 MuJoCo FK 결과인

\[
\mathbf p_k=\mathbf p(\mathbf q_k)
\]

이고 위치 오차는

\[
\mathbf e_k=\mathbf p_d-\mathbf p_k
\]

로 정의한다. 코드에서는 `target - data.site_xpos[tip_id]`에 해당한다.

종료 조건은

\[
\|\mathbf e_k\|_2\le 10^{-4}\text{ m}
\]

즉 0.1 mm다. 목표가 도달 불가능하거나 특이점 때문에 오차를 더 줄이지
못하면 한 렌더 프레임의 최대 15회 반복 후 현재까지 얻은 자세를 사용하고,
다음 프레임에서 다시 계산한다.

## 3. Jacobian에 의한 국소 선형화

작은 관절 변화 \(\Delta\mathbf q\)에 대한 TCP 위치 변화는 1차 근사로

\[
\Delta\mathbf p\approx J_p(\mathbf q_k)\Delta\mathbf q
\]

이다. 여기서 위치 Jacobian은

\[
J_p=\frac{\partial\mathbf p}{\partial\mathbf q}
=
\begin{bmatrix}
\frac{\partial p_x}{\partial q_1}&\cdots&
\frac{\partial p_x}{\partial q_4}\\
\frac{\partial p_y}{\partial q_1}&\cdots&
\frac{\partial p_y}{\partial q_4}\\
\frac{\partial p_z}{\partial q_1}&\cdots&
\frac{\partial p_z}{\partial q_4}
\end{bmatrix}
\in\mathbb R^{3\times4}.
\]

코드는 유한차분으로 Jacobian을 근사하지 않고 MuJoCo의
`mj_jacSite`를 호출한다. MuJoCo가 현재 body tree와 joint axis로부터
해석적으로 전체 \(3\times n_v\) 위치 Jacobian을 만든 뒤, 코드가 네 관절의
DOF 열만 선택한다.

revolute joint의 각 열은 기하학적으로

\[
J_{p,i}=\mathbf z_i\times(\mathbf p-\mathbf o_i)
\]

이다. \(\mathbf z_i\)는 관절축의 월드 방향, \(\mathbf o_i\)는 관절 원점,
\(\mathbf p\)는 TCP 위치다.

## 4. 단순 역행렬 대신 DLS를 쓰는 이유

원하는 국소 변화는

\[
J_p\Delta\mathbf q\approx\mathbf e
\]

를 만족해야 한다. 그러나 \(J_p\)는 3×4 행렬이라 정방행렬이 아니며,
특이 자세에서는 rank가 감소할 수 있다. 단순 의사역행렬은 작은 singular
value의 역수를 크게 만들기 때문에 미세한 위치 오차가 매우 큰 관절 변화로
증폭될 수 있다.

DLS는 다음 정규화된 최소제곱 문제로 볼 수 있다.

\[
\Delta\mathbf q^*
=\arg\min_{\Delta\mathbf q}
\left(
\|J_p\Delta\mathbf q-\mathbf e\|_2^2
+\lambda^2\|\Delta\mathbf q\|_2^2
\right).
\]

첫 항은 Cartesian 오차를 줄이고, 두 번째 항은 큰 관절 변화를 벌점으로
준다. 이 문제의 해는

\[
\Delta\mathbf q
=J_p^T(J_pJ_p^T+\lambda^2I_3)^{-1}\mathbf e
\]

이다. 코드에서는 수치적으로 역행렬을 직접 만들지 않고

\[
(J_pJ_p^T+\lambda^2I_3)\mathbf y=\mathbf e
\]

를 `numpy.linalg.solve`로 푼 후

\[
\Delta\mathbf q=J_p^T\mathbf y
\]

를 계산한다. 명시적 `inv`보다 이 방식이 일반적으로 수치적으로 안정적이다.

## 5. 감쇠계수와 step size

현재 파라미터는 과거 jdCobot200 수치 IK의 값을 따라 다음과 같이 설정했다.

| 파라미터 | 코드 값 | 의미 |
|---|---:|---|
| \(\lambda\) | 0.03 | DLS 감쇠계수 |
| \(\alpha\) | 0.6 | 관절 업데이트 step size |
| 반복 횟수 | 15/frame | 렌더 프레임당 최대 내부 반복 |
| tolerance | 0.0001 m | 종료 위치 오차 |
| Cartesian jog | 0.005 m | 키 입력 한 번당 목표 이동 |

최종 관절 업데이트는

\[
\mathbf q_{k+1}
=\operatorname{clip}\left(
\mathbf q_k+\alpha\Delta\mathbf q,
\mathbf q_{min},\mathbf q_{max}
\right)
\]

이다.

\(\lambda\)를 크게 하면 특이점 부근에서 더 안정적이지만 수렴이 느리고
정상상태 오차가 커질 수 있다. 작게 하면 의사역행렬에 가까워져 빠르고
정확할 수 있지만 특이점 근처에서 큰 관절 변화가 생기기 쉽다.

\(\alpha\)는 비선형 FK를 선형 Jacobian으로 근사하면서 한 번에 너무 멀리
가지 않도록 하는 계수다. \(\alpha=1\)보다 작은 0.6을 사용해 overshoot와
진동 가능성을 줄인다.

## 6. 한 번의 DLS solve 과정

현재 코드의 `solve_dls()`는 다음 순서로 작동한다.

1. 현재 네 관절각을 \(\mathbf q\)로 복사한다.
2. `data.qpos`에 \(\mathbf q\)를 적용한다.
3. `mj_forward`로 모든 body 위치를 다시 계산한다.
4. \(\mathbf e=\mathbf p_d-\mathbf p(\mathbf q)\)를 계산한다.
5. 오차가 0.1 mm 이하이면 반복을 종료한다.
6. `mj_jacSite`로 `tcp_site`의 위치 Jacobian을 계산한다.
7. 로봇의 네 DOF에 해당하는 열만 추출한다.
8. \(J_pJ_p^T+\lambda^2I\) 선형시스템을 푼다.
9. \(\mathbf q\leftarrow\operatorname{clip}(\mathbf q+alpha\Delta\mathbf q)\)로
   갱신한다.
10. 최대 15회까지 2~9를 반복한다.
11. 결과를 `data.qpos`에 기록하고 GLFW로 렌더링한다.

의사코드는 다음과 같다.

```text
q = current_q
repeat at most 15 times:
    p = forward_kinematics(q)
    e = target - p
    if norm(e) <= 0.0001:
        break

    J = mujoco_position_jacobian(q)
    y = solve(J @ J.T + 0.03^2 * I, e)
    delta_q = J.T @ y
    q = clip(q + 0.6 * delta_q, q_min, q_max)
apply(q)
```

## 7. 3 cm TCP site와 position-only IK의 자유도

현재 task는 위치 XYZ 세 성분만 제어하고 말단 orientation은 제어하지 않는다.
TCP는 `end_arm_sub_assembly`의 로컬 위치

\[
{}^4\mathbf p_{TCP}=\begin{bmatrix}-0.03&0&0\end{bmatrix}^T
\]

에 정의되어 있다. J4 축에서 3 cm 떨어져 있으므로 J4 회전에 따른 위치
변화는 일반적으로 0이 아니며

\[
J_{p,4}=\mathbf z_4\times(\mathbf p_{TCP}-\mathbf o_4)
\]

가 위치 IK에 포함된다. 따라서 4개의 관절로 XYZ 세 성분을 제어하고 남는
하나의 자유도를 DLS가 최소 관절 변화 해를 선택하는 데 사용할 수 있다.
다만 위치만 제어하므로 최종 end-arm orientation은 명시적으로 지정되지 않는다.

뷰어에는 `tcp_site`가 반지름 3 mm의 밝은 녹색 구로 표시된다. 말단
orientation까지 제어하려면 위치 오차뿐 아니라 회전 오차와 회전 Jacobian을
포함한 task가 필요하다.

## 8. 키 입력에서 IK 목표까지

목표 위치는 월드 좌표계에서 누적된다.

| 축 | 증가 | 감소 | 변화량 |
|---|---:|---:|---:|
| X | `W` | `S` | 5 mm |
| Y | `A` | `D` | 5 mm |
| Z | `R` | `F` | 5 mm |

예를 들어 `W`를 한 번 누르면

\[
\mathbf p_d\leftarrow
\mathbf p_d+
\begin{bmatrix}0.005\\0\\0\end{bmatrix}
\]

이다. `0`은 관절을 home으로 되돌리고 그때의 TCP 위치를 새 목표로 설정한다.

```bash
python3 -m ros_arm.mujoco_ik
```

## 9. 현재 프로토타입에서 의도적으로 제외한 항목

요청한 초기 프로토타입 범위에 따라 다음은 DLS 목적함수나 반복 전후에
검사하지 않는다.

- 바닥 충돌 검사
- 링크 간 self-collision 검사
- 목표까지의 보간 경로 안전성 검사
- 도달 가능 영역 사전 판정
- joint velocity/acceleration 기반 trajectory 생성

관절각은 MJCF의 \([-\pi,\pi]\) 범위로 clipping한다. 도달 불가능한 목표에서는
예외를 발생시키기보다 관절 제한 또는 국소 최소점에서 멈추고 남은 위치 오차를
터미널에 표시한다.
