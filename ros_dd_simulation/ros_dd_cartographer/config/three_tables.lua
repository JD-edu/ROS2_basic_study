-- ros_dd_cartographer/config/ros_dd_cartographer.lua
-- 터틀봇 설정을 기반으로 ros_dd_gazebo에 맞게 수정

include "map_builder.lua"
include "trajectory_builder.lua"

options = {
  map_builder = MAP_BUILDER,
  trajectory_builder = TRAJECTORY_BUILDER,
  map_frame = "map",
  
  -- 🌟 1. 로봇의 Lidar 프레임으로 변경 (필수) 🌟
  tracking_frame = "base_footprint", 
  
  -- Cartographer가 발행할 TF 프레임 (map -> published_frame)
  published_frame = "odom", 
  odom_frame = "odom",
  
  -- Gazebo가 이미 odom -> base_footprint TF를 발행하므로 false 유지
  provide_odom_frame = false,
  
  publish_frame_projected_to_2d = true,
  
  -- Odometry 사용 (Gazebo Diff Drive)
  use_odometry = true, 
  
  use_nav_sat = false,
  
  use_landmarks = false,
  num_laser_scans = 1,
  num_multi_echo_laser_scans = 0,
  num_subdivisions_per_laser_scan = 1,
  num_point_clouds = 0,
  lookup_transform_timeout_sec = 0.2,
  submap_publish_period_sec = 0.3,
  pose_publish_period_sec = 5e-3,
  trajectory_publish_period_sec = 30e-3,
  rangefinder_sampling_ratio = 1.,
  odometry_sampling_ratio = 1.,
  fixed_frame_pose_sampling_ratio = 1.,
  imu_sampling_ratio = 1.,
  landmarks_sampling_ratio = 1.,
}

MAP_BUILDER.use_trajectory_builder_2d = true

-- ***************************************************************
-- 2D Trajectory Builder Options
-- ***************************************************************
TRAJECTORY_BUILDER_2D.min_range = 0.1
-- 🌟 3. Lidar 최대 범위에 맞춤 (8.0m) 🌟
TRAJECTORY_BUILDER_2D.max_range = 8.0 
TRAJECTORY_BUILDER_2D.missing_data_ray_length = 3.

-- 🌟 IMU 사용 'false'로 유지 (터틀봇 원본과 동일) 🌟
TRAJECTORY_BUILDER_2D.use_imu_data = false 
TRAJECTORY_BUILDER_2D.use_online_correlative_scan_matching = true 
TRAJECTORY_BUILDER_2D.motion_filter.max_angle_radians = math.rad(0.1)

-- POSE_GRAPH.optimize_every_n_nodes = 0

return options