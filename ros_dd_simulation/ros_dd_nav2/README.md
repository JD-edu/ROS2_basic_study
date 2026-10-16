# Terminal navigation goals

Start Gazebo and your Nav2/localization stack first, then run:

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run ros_dd_nav2 goto_pose --ros-args -p use_sim_time:=true
```

Enter `x y` in meters in the **map frame**, one goal per line. Optionally add
`yaw` in degrees, for example `1.0 2.0 90`. Omitted yaw means 0 degrees (+X).

The node sends a `nav2_msgs/action/NavigateToPose` action to `/navigate_to_pose`.
It does not publish `/cmd_vel`, initialize AMCL, or start/stop Nav2 lifecycle nodes.
Use a relative action name so normal ROS remapping/namespaces still apply.
Goals wait for the action server when it is unavailable. Localization and Nav2
must already be ready for navigation.

While moving, enter new coordinates to cancel the current goal and send the
latest requested goal after the previous goal has finished canceling. If several
new inputs arrive during cancellation, only the latest is sent. Input remains
available after arrival, rejection, or failure.

- `cancel`: discard a queued goal and cancel the current goal.
- `q`, `quit`, `exit`, Ctrl+D, or Ctrl+C: discard queued goals, request cancellation,
  wait up to three seconds for acknowledgement, then exit. Nav2 remains running.
- Invalid or non-finite coordinates are rejected without changing the current goal.

For a real robot/real clock omit `-p use_sim_time:=true`.
