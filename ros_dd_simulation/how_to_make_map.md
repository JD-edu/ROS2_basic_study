source  /usr/share/gazebo/setup.sh

ros2 launch ros_dd_gazebo ros_dd.launch.py

ros2 launch ros_dd_cartographer ros_dd_cartograph.launch.py use_sim_time:=True 

ros2  run  ros_dd_teleop asdw_teleop 

ros2 run nav2_map_server map_saver_cli -f ~/map

