# ros_dd_simulation — ROS 2 Jazzy / Gazebo Harmonic

Ubuntu 24.04, ROS 2 Jazzy, Gazebo Harmonic (`gz sim`). Package and launch names
are retained. Gazebo Classic / `gazebo_ros` are no longer used.

## Install and build

```bash
sudo apt-get update
sudo apt-get install ros-jazzy-ros-gz ros-jazzy-xacro ros-jazzy-navigation2 ros-jazzy-nav2-bringup ros-jazzy-cartographer-ros
cd ~/ros2_ws
source /opt/ros/jazzy/setup.bash
rosdep install --from-paths src/ros_dd_simulation --ignore-src -r -y --rosdistro jazzy
colcon build --base-paths src/ros_dd_simulation
source install/setup.bash
```

Build from the workspace root, not `src/`. Source `~/ros2_ws/install/setup.bash`
in each terminal after sourcing Jazzy. The old `src/install` tree contains stale
build artifacts and should not be sourced.

## Simulator

```bash
ros2 launch ros_dd_gazebo ros_dd_xacro.launch.py
# Direct URDF entry point:
ros2 launch ros_dd_gazebo ros_dd.launch.py
# Server only (GPU lidar still requires a working rendering context):
ros2 launch ros_dd_gazebo ros_dd_xacro.launch.py gz_args:="-r -s"
```

`ros_dd_xacro.launch.py` expands `ros_dd_description/urdf/ros_dd.xacro` at launch.
`ros_dd.launch.py` reads the saved `ros_dd_description/urdf/ros_dd.urdf` directly
and starts Gazebo, robot_state_publisher, model creation and the bridge itself.
It does not include another launch file or run Xacro. Regenerate the saved URDF
after editing Xacro if you want both entry points to use the same model:

```bash
xacro src/ros_dd_simulation/ros_dd_description/urdf/ros_dd.xacro -o src/ros_dd_simulation/ros_dd_description/urdf/ros_dd.urdf
colcon build --base-paths src/ros_dd_simulation --packages-select ros_dd_description
```
The world includes local ground and sun definitions, with no Classic model database
or `/usr/share/gazebo/setup.sh` dependency. Custom worlds must expose the world name
`default` for the model spawner and provide physics, user commands, scene broadcaster,
sensors (Ogre2), and IMU systems as in `ros_dd.world`.

`config/bridge.yaml` bridges `/clock`, `/odom`, `/tf`, `/joint_states`, `/scan`,
and `/imu/data` from Gazebo to ROS; `/cmd_vel` (`geometry_msgs/msg/Twist`) flows
from ROS to Gazebo. Nav2 and teleop use the same Twist interface. DiffDrive publishes
`odom -> base_footprint`; robot_state_publisher publishes the remaining transforms.
All simulation launch files default to `use_sim_time:=true`.

## Mapping

Run simulator, Cartographer and teleop in separate terminals:

```bash
ros2 launch ros_dd_cartographer ros_dd_cartograph.launch.py
ros2 run ros_dd_teleop asdw_teleop
ros2 run nav2_map_server map_saver_cli -f ~/map --ros-args -p use_sim_time:=true
```

## Navigation

For a saved map, stop Cartographer first (AMCL provides `map -> odom`):

```bash
ros2 launch ros_dd_navigation navigation.launch.py map:=$HOME/map.yaml
```

Set the initial pose with RViz **2D Pose Estimate**, then set a navigation goal.
If `map` is omitted, the bundled existing map is loaded; regenerate it if it no
longer matches the world. To navigate while Cartographer is running instead:

```bash
ros2 launch ros_dd_navigation navigation.launch.py use_localization:=false
```

This disables AMCL and map_server to avoid competing map and TF publishers.
Use `use_rviz:=false` for navigation without RViz. The terminal goal client works with either localization mode:
`ros2 run ros_dd_nav2 goto_pose --ros-args -p use_sim_time:=true`.
Enter `x y [yaw_degrees]` repeatedly; `cancel` cancels and `q` exits.

## Verification after installation

```bash
ros2 topic echo /clock --once
ros2 topic echo /scan --once --qos-reliability best_effort
ros2 topic echo /imu/data --once --qos-reliability best_effort
ros2 topic echo /joint_states --once
ros2 topic echo /odom --once
ros2 run tf2_ros tf2_echo odom base_footprint
ros2 run tf2_ros tf2_echo base_footprint laser_link
# Publish a short command while observing odometry (Ctrl-C to finish):
ros2 topic pub -r 10 /cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.1}}'
ros2 topic pub --once /cmd_vel geometry_msgs/msg/Twist '{}'
```

Migration references: [Gazebo Harmonic migration](https://gazebosim.org/docs/harmonic/migrating_gazebo_classic_ros2_packages/),
[Nav2 migration guides](https://docs.nav2.org/migration/index.html).

## Migration validation in this workspace

All seven packages built on Jazzy. Three configuration regression tests passed;
Xacro expansion, `check_urdf`, manifests, Python/XML/YAML syntax and installed
model/bridge/map assets were checked. After the system dependencies were installed,
Gazebo Harmonic 8.15.0 was run both server-only and with the GUI through
`ros_dd.launch.py`. Robot creation and visible rendering were confirmed. ROS
`/odom`, `/imu/data` (base_link), and `/scan` (laser_link, 360 samples) were received;
a 0.1 m/s command for two seconds produced approximately 0.19 m odometry displacement.
SLAM and end-to-end Nav2 navigation have not been tested.

The packaged `config/gui.config` sets a closer initial camera view so the small
red/yellow robot is easier to locate. The Entity Tree names it `ros_dd_robot`.
Override it with `gui_config:=/absolute/path/to/gui.config` if desired. EGL and
`gz_frame_id` warnings were also emitted during the successful runs; those warnings
alone did not prevent creation, rendering or sensor publication on this machine.

## RViz startup and initial localization

The navigation launch uses the package-owned `rviz/navigation.rviz` with standard
RViz displays and tools, without Nav2's additional GUI panels. Set the initial pose
using **2D Pose Estimate**, then publish a goal using **2D Goal Pose** (`/goal_pose`).
The map can be displayed before AMCL has an initial pose. Until an initial pose
and scans are received, AMCL cannot publish `map -> odom`, so planner TF waits
are expected. Map loading success does not imply localization is initialized.

`rviz_config:=/absolute/path/to/config.rviz` selects another view. An optional
`rviz_software_rendering:=true` flag affects RViz only. It was tested and did not
eliminate this machine's sampler shader diagnostic; it is not a confirmed fix.

## Three-table world: mapping and saved-map navigation

The workflow is now separated. `three_tables_mapping.launch.py` starts Gazebo +
Cartographer without Nav2. Save the map and stop mapping, then run
`three_tables_navigation.launch.py map:=/absolute/path/to/map.yaml`, which starts
Gazebo + map_server + AMCL + Nav2 without Cartographer. The `map` argument is required.
See [THREE_TABLES.md](THREE_TABLES.md) for commands and localization steps.
Harness and LLM code are unchanged and neither is started by these launches.
