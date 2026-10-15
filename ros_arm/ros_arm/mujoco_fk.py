"""Keyboard joint-space (FK) demo for the four-axis ros_arm."""

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


KEY_BINDINGS = {
    ord("1"): (0, 1.0),
    ord("q"): (0, -1.0),
    ord("2"): (1, 1.0),
    ord("w"): (1, -1.0),
    ord("3"): (2, 1.0),
    ord("e"): (2, -1.0),
    ord("4"): (3, 1.0),
    ord("r"): (3, -1.0),
}


def main() -> None:
    """Run the interactive forward-kinematics viewer."""
    model = load_scene_model()
    data = mujoco.MjData(model)
    addresses = joint_addresses(model)
    tip_id = site_id(model)
    set_home(model, data)
    target_q = data.qpos[addresses].copy()
    step = np.deg2rad(5.0)

    def on_key(keycode: int) -> None:
        nonlocal target_q
        key = chr(keycode).lower() if 0 <= keycode < 256 else ""
        binding = KEY_BINDINGS.get(ord(key)) if key else None
        if binding is not None:
            index, direction = binding
            target_q[index] += direction * step
            target_q[index] = np.clip(
                target_q[index],
                model.jnt_range[index, 0],
                model.jnt_range[index, 1],
            )
        elif key == "0":
            target_q = HOME_QPOS.copy()

    print("\n[ros_arm FK]")
    print("  J1: 1/Q  J2: 2/W  J3: 3/E  J4: 4/R (+/- 5 deg)")
    print("  Home: 0, Exit: ESC")

    with GLFWRenderer(
        model, data, "ros_arm - MuJoCo GLFW FK", on_key
    ) as viewer:
        last_report = 0.0
        while viewer.is_running():
            data.qpos[addresses] += 0.18 * (
                target_q - data.qpos[addresses]
            )
            data.qvel[:] = 0.0
            mujoco.mj_forward(model, data)
            viewer.render()

            now = time.monotonic()
            if now - last_report >= 0.5:
                degrees = np.rad2deg(data.qpos[addresses])
                xyz = data.site_xpos[tip_id]
                joint_text = ", ".join(
                    f"{name}={value:6.1f}"
                    for name, value in zip(JOINT_NAMES, degrees)
                )
                print(
                    f"\r{joint_text} deg | TCP xyz={xyz.round(4)} m",
                    end="",
                    flush=True,
                )
                last_report = now
            time.sleep(1.0 / 60.0)
    print()


if __name__ == "__main__":
    main()
