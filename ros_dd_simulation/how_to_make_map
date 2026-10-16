ROS 2 Jazzy / Gazebo Harmonic — see README.md for installation.
In separate terminals, source ~/ros2_ws/install/setup.bash, then run:

ros2 launch ros_dd_gazebo ros_dd.launch.py
ros2 launch ros_dd_cartographer ros_dd_cartograph.launch.py use_sim_time:=true
ros2 run ros_dd_teleop asdw_teleop
ros2 run nav2_map_server map_saver_cli -f ~/map --ros-args -p use_sim_time:=true
