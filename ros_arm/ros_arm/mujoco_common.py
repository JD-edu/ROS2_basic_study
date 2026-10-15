"""Shared MuJoCo helpers for the four-axis ros_arm examples."""

from __future__ import annotations

from pathlib import Path
from typing import Callable

import glfw
import mujoco
import numpy as np


JOINT_NAMES = (
    "base_shoulder",
    "shoulder_arm1",
    "arm1_arm2",
    "arn2_end_arm",
)
END_EFFECTOR_BODY = "end_arm_sub_assembly"
TCP_SITE = "tcp_site"
HOME_QPOS = np.deg2rad([0.0, -35.0, 70.0, -35.0])


def package_root() -> Path:
    """Return the source or installed package root containing the MJCF."""
    source_root = Path(__file__).resolve().parents[1]
    if (source_root / "mjcf" / "scene.xml").is_file():
        return source_root

    try:
        from ament_index_python.packages import get_package_share_directory
    except ImportError as exc:
        raise FileNotFoundError(
            "ros_arm source directory was not found and ament_index_python "
            "is unavailable."
        ) from exc
    return Path(get_package_share_directory("ros_arm"))


def load_scene_model() -> mujoco.MjModel:
    """Load the lit scene, which includes the converted robot MJCF."""
    root = package_root()
    model = mujoco.MjModel.from_xml_path(str(root / "mjcf" / "scene.xml"))
    model.opt.gravity[:] = 0.0
    model.opt.timestep = 0.01
    return model


def load_urdf_model() -> mujoco.MjModel:
    """Backward-compatible alias for callers of the initial prototype."""
    return load_scene_model()


def joint_addresses(model: mujoco.MjModel) -> np.ndarray:
    """Resolve the four arm joint qpos addresses in kinematic order."""
    addresses = []
    for name in JOINT_NAMES:
        joint_id = mujoco.mj_name2id(
            model, mujoco.mjtObj.mjOBJ_JOINT, name
        )
        if joint_id < 0:
            raise ValueError(f"URDF에 관절 '{name}'이 없습니다.")
        addresses.append(model.jnt_qposadr[joint_id])
    return np.asarray(addresses, dtype=int)


def body_id(model: mujoco.MjModel, name: str = END_EFFECTOR_BODY) -> int:
    """Resolve a required body ID or raise a useful error."""
    result = mujoco.mj_name2id(model, mujoco.mjtObj.mjOBJ_BODY, name)
    if result < 0:
        raise ValueError(f"URDF에 body '{name}'이 없습니다.")
    return int(result)


def site_id(model: mujoco.MjModel, name: str = TCP_SITE) -> int:
    """Resolve a required site ID or raise a useful error."""
    result = mujoco.mj_name2id(model, mujoco.mjtObj.mjOBJ_SITE, name)
    if result < 0:
        raise ValueError(f"MJCF에 site '{name}'이 없습니다.")
    return int(result)


def set_home(model: mujoco.MjModel, data: mujoco.MjData) -> None:
    """Put the model in a non-singular demonstration pose."""
    data.qpos[joint_addresses(model)] = HOME_QPOS
    data.qvel[:] = 0.0
    mujoco.mj_forward(model, data)


class GLFWRenderer:
    """Small standalone GLFW renderer for a MuJoCo model."""

    def __init__(
        self,
        model: mujoco.MjModel,
        data: mujoco.MjData,
        title: str,
        key_handler: Callable[[int], None],
        width: int = 1000,
        height: int = 700,
    ) -> None:
        self.model = model
        self.data = data
        self.key_handler = key_handler
        self.window = None
        self.context = None

        if not glfw.init():
            raise RuntimeError(
                "GLFW 초기화 실패: DISPLAY와 그래픽 드라이버를 확인하세요."
            )
        try:
            glfw.window_hint(glfw.SAMPLES, 4)
            self.window = glfw.create_window(
                width, height, title, None, None
            )
            if self.window is None:
                raise RuntimeError("GLFW 창을 생성할 수 없습니다.")
            glfw.make_context_current(self.window)
            glfw.swap_interval(1)

            self.camera = mujoco.MjvCamera()
            mujoco.mjv_defaultCamera(self.camera)
            self.camera.lookat[:] = [0.0, 0.0, 0.10]
            self.camera.distance = 0.45
            self.camera.azimuth = 135.0
            self.camera.elevation = -25.0

            self.option = mujoco.MjvOption()
            mujoco.mjv_defaultOption(self.option)
            self.scene = mujoco.MjvScene(model, maxgeom=10_000)
            self.context = mujoco.MjrContext(
                model, mujoco.mjtFontScale.mjFONTSCALE_150.value
            )
            self._mouse_buttons = {
                "left": False,
                "middle": False,
                "right": False,
            }
            self._mouse_x = 0.0
            self._mouse_y = 0.0
            self._install_callbacks()
        except Exception:
            self.close()
            raise

    def _install_callbacks(self) -> None:
        def on_key(window, key, _scancode, action, _mods):
            if action not in (glfw.PRESS, glfw.REPEAT):
                return
            if key == glfw.KEY_ESCAPE:
                glfw.set_window_should_close(window, True)
                return
            self.key_handler(key)

        def on_button(window, _button, _action, _mods):
            self._mouse_buttons["left"] = (
                glfw.get_mouse_button(window, glfw.MOUSE_BUTTON_LEFT)
                == glfw.PRESS
            )
            self._mouse_buttons["middle"] = (
                glfw.get_mouse_button(window, glfw.MOUSE_BUTTON_MIDDLE)
                == glfw.PRESS
            )
            self._mouse_buttons["right"] = (
                glfw.get_mouse_button(window, glfw.MOUSE_BUTTON_RIGHT)
                == glfw.PRESS
            )
            self._mouse_x, self._mouse_y = glfw.get_cursor_pos(window)

        def on_cursor(window, xpos, ypos):
            dx = xpos - self._mouse_x
            dy = ypos - self._mouse_y
            self._mouse_x = xpos
            self._mouse_y = ypos
            if not any(self._mouse_buttons.values()):
                return

            _, height = glfw.get_window_size(window)
            shift = (
                glfw.get_key(window, glfw.KEY_LEFT_SHIFT) == glfw.PRESS
                or glfw.get_key(window, glfw.KEY_RIGHT_SHIFT) == glfw.PRESS
            )
            if self._mouse_buttons["right"]:
                action = (
                    mujoco.mjtMouse.mjMOUSE_MOVE_H
                    if shift
                    else mujoco.mjtMouse.mjMOUSE_MOVE_V
                )
            elif self._mouse_buttons["left"]:
                action = (
                    mujoco.mjtMouse.mjMOUSE_ROTATE_H
                    if shift
                    else mujoco.mjtMouse.mjMOUSE_ROTATE_V
                )
            else:
                action = mujoco.mjtMouse.mjMOUSE_ZOOM
            mujoco.mjv_moveCamera(
                self.model,
                action,
                dx / max(height, 1),
                dy / max(height, 1),
                self.scene,
                self.camera,
            )

        def on_scroll(_window, _xoffset, yoffset):
            mujoco.mjv_moveCamera(
                self.model,
                mujoco.mjtMouse.mjMOUSE_ZOOM,
                0.0,
                -0.05 * yoffset,
                self.scene,
                self.camera,
            )

        glfw.set_key_callback(self.window, on_key)
        glfw.set_mouse_button_callback(self.window, on_button)
        glfw.set_cursor_pos_callback(self.window, on_cursor)
        glfw.set_scroll_callback(self.window, on_scroll)

    def is_running(self) -> bool:
        """Return whether the window is still open."""
        return (
            self.window is not None
            and not glfw.window_should_close(self.window)
        )

    def render(self) -> None:
        """Draw the current MjData state and process window events."""
        if not self.is_running():
            return
        glfw.make_context_current(self.window)
        width, height = glfw.get_framebuffer_size(self.window)
        viewport = mujoco.MjrRect(0, 0, width, height)
        mujoco.mjv_updateScene(
            self.model,
            self.data,
            self.option,
            None,
            self.camera,
            mujoco.mjtCatBit.mjCAT_ALL.value,
            self.scene,
        )
        mujoco.mjr_render(viewport, self.scene, self.context)
        glfw.swap_buffers(self.window)
        glfw.poll_events()

    def close(self) -> None:
        """Release MuJoCo and GLFW resources."""
        if self.context is not None:
            self.context.free()
            self.context = None
        if self.window is not None:
            glfw.destroy_window(self.window)
            self.window = None
        glfw.terminate()

    def __enter__(self) -> "GLFWRenderer":
        return self

    def __exit__(self, _exc_type, _exc_value, _traceback) -> None:
        self.close()
