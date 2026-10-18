"""Validate saved-map inputs and prevent conflicting mapping/navigation launches."""
from pathlib import Path
import time

import yaml


def validate_map_file(filename):
    """Return an absolute map path after checking its YAML and image."""
    path = Path(filename).expanduser().resolve()
    if not path.is_file():
        raise RuntimeError(f'Map YAML file does not exist: {path}')
    with path.open(encoding='utf-8') as stream:
        data = yaml.safe_load(stream)
    if not isinstance(data, dict) or not isinstance(data.get('image'), str):
        raise RuntimeError(f'Map YAML must contain an image path: {path}')
    image = Path(data['image']).expanduser()
    if not image.is_absolute():
        image = path.parent / image
    if not image.is_file():
        raise RuntimeError(f'Map image does not exist: {image}')
    return str(path)


def assert_mode_available(mode, start_simulation=True):
    """Reject already-running SLAM/navigation in the current ROS domain."""
    import rclpy
    from rclpy.context import Context
    from rclpy.executors import SingleThreadedExecutor
    from rclpy.signals import SignalHandlerOptions
    from rcl_interfaces.srv import GetParameters

    context = Context()
    rclpy.init(args=[], context=context, signal_handler_options=SignalHandlerOptions.NO)
    node = rclpy.create_node('three_tables_launch_check', context=context,
                             enable_rosout=False, start_parameter_services=False)
    executor = SingleThreadedExecutor(context=context)
    executor.add_node(node)
    try:
        deadline = time.monotonic() + 2.0
        names = set()
        while time.monotonic() < deadline:
            executor.spin_once(timeout_sec=0.1)
            names.update(node.get_node_names())
        def responds(name):
            # DDS discovery can retain a departed participant briefly. Do not
            # mistake that cached name for a still-running process.
            client = node.create_client(GetParameters, f'/{name}/get_parameters')
            try:
                if not client.wait_for_service(timeout_sec=0.3):
                    return False
                future = client.call_async(GetParameters.Request())
                executor.spin_until_future_complete(future, timeout_sec=1.0)
                return future.done() and future.exception() is None and future.result() is not None
            finally:
                node.destroy_client(client)

        candidates = names.intersection({
            'cartographer_node', 'cartographer_occupancy_grid_node',
            'map_server', 'amcl', 'planner_server', 'controller_server', 'bt_navigator',
        })
        conflicts = {name for name in candidates if responds(name)}
        if conflicts:
            raise RuntimeError(
                f'Cannot start three-table {mode}: already running {sorted(conflicts)}. '
                'Stop the previous mapping/navigation launch with Ctrl+C first; '
                'use a separate ROS_DOMAIN_ID for an independent simulation.')
        if (start_simulation and 'robot_state_publisher' in names
                and responds('robot_state_publisher')):
            raise RuntimeError(
                'A robot simulation is already running. Stop it first, or use '
                'start_simulation:=false to reuse the existing three-table world.')
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown(context=context)
