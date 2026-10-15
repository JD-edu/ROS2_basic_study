"""MuJoCo Jacobian DLS IK demo for the four-axis ros_arm."""

from __future__ import annotations

import time

import mujoco
import numpy as np

from ros_arm.mujoco_common import (
    GLFWRenderer,
    HOME_QPOS,
    JOINT_NAMES,
    joint_addresses,
    load_scene_model,
    set_home,
    site_id,
)


TARGET_DELTAS = {
    ord("w"): np.array([1.0, 0.0, 0.0]),
    ord("s"): np.array([-1.0, 0.0, 0.0]),
    ord("a"): np.array([0.0, 1.0, 0.0]),
    ord("d"): np.array([0.0, -1.0, 0.0]),
    ord("r"): np.array([0.0, 0.0, 1.0]),
    ord("f"): np.array([0.0, 0.0, -1.0]),
}


def main() -> None:
    """Run the JDCobot200-style Jacobian DLS Cartesian jogger."""
    model = load_scene_model()
    data = mujoco.MjData(model)
    addresses = joint_addresses(model)
    tip_id = site_id(model)
    set_home(model, data)

    joint_ids = np.array(
        [model.joint(name).id for name in JOINT_NAMES],
        dtype=int,
    )
    dof_addresses = model.jnt_dofadr[joint_ids].astype(int)
    lower = model.jnt_range[joint_ids, 0].copy()
    upper = model.jnt_range[joint_ids, 1].copy()
    jacobian_position = np.zeros((3, model.nv), dtype=float)
    jacobian_rotation = np.zeros((3, model.nv), dtype=float)

    target = data.site_xpos[tip_id].copy()
    step = 0.005
    iterations = 15
    step_size = 0.6
    damping = 0.03
    tolerance = 1e-4

    def reset_home() -> None:
        nonlocal target
        data.qpos[addresses] = HOME_QPOS
        data.qvel[:] = 0.0
        mujoco.mj_forward(model, data)
        target = data.site_xpos[tip_id].copy()

    def on_key(keycode: int) -> None:
        nonlocal target
        key = chr(keycode).lower() if 0 <= keycode < 256 else ""
        delta = TARGET_DELTAS.get(ord(key)) if key else None
        if delta is not None:
            target = target + step * delta
        elif key == "0":
            reset_home()

    def solve_dls() -> float:
        """Apply several damped-least-squares iterations in place."""
        q = data.qpos[addresses].copy()
        error_norm = float("inf")
        for _ in range(iterations):
            data.qpos[addresses] = q
            data.qvel[:] = 0.0
            mujoco.mj_forward(model, data)

            error = target - data.site_xpos[tip_id]
            error_norm = float(np.linalg.norm(error))
            if error_norm <= tolerance:
                break

            mujoco.mj_jacSite(
                model,
                data,
                jacobian_position,
                jacobian_rotation,
                tip_id,
            )
            jacobian = jacobian_position[:, dof_addresses]
            regularized = (
                jacobian @ jacobian.T
                + damping ** 2 * np.eye(3)
            )
            delta_q = jacobian.T @ np.linalg.solve(
                regularized, error
            )
            q = np.clip(
                q + step_size * delta_q,
                lower,
                upper,
            )

        data.qpos[addresses] = q
        data.qvel[:] = 0.0
        mujoco.mj_forward(model, data)
        return float(np.linalg.norm(target - data.site_xpos[tip_id]))

    print("\n[ros_arm IK - MuJoCo Jacobian DLS position IK]")
    print("  X: W/S  Y: A/D  Z: R/F (+/- 5 mm)")
    print("  Home/target reset: 0, Exit: ESC")
    print("  Prototype: floor/self collision and path pre-check are disabled.")

    dt = 1.0 / 60.0
    with GLFWRenderer(
        model, data, "ros_arm - MuJoCo GLFW IK", on_key
    ) as viewer:
        last_report = 0.0
        while viewer.is_running():
            error_m = solve_dls()
            viewer.render()

            now = time.monotonic()
            if now - last_report >= 0.25:
                current = data.site_xpos[tip_id].copy()
                print(
                    f"\rtarget={target.round(4)} m | "
                    f"TCP={current.round(4)} m | "
                    f"error={1000.0 * error_m:5.2f} mm",
                    end="",
                    flush=True,
                )
                last_report = now
            time.sleep(dt)
    print()


if __name__ == "__main__":
    main()
