"""Check the contracts between robot sensors, Gazebo systems and ROS bridges."""
from pathlib import Path
import xml.etree.ElementTree as ET

import yaml


ROOT = Path(__file__).resolve().parents[2]


def test_sensor_topics_and_frames_match_bridges_and_robot():
    """Every Gazebo sensor must reach ROS with a frame in the robot TF tree."""
    robot = ET.parse(ROOT / 'ros_dd_description/urdf/ros_dd.urdf').getroot()
    bridges = yaml.safe_load((ROOT / 'ros_dd_gazebo/config/bridge.yaml').read_text())
    by_topic = {bridge['gz_topic_name']: bridge for bridge in bridges}
    links = {link.attrib['name'] for link in robot.findall('link')}
    sensors = robot.findall('.//sensor')
    assert {sensor.attrib['type'] for sensor in sensors} == {'imu', 'gpu_lidar'}
    for sensor in sensors:
        assert sensor.findtext('gz_frame_id') in links
        bridge = by_topic[sensor.findtext('topic')]
        assert bridge['direction'] == 'GZ_TO_ROS'
        assert bridge['qos_profile'] == 'SENSOR_DATA'
    drive = robot.find(".//plugin[@name='gz::sim::systems::DiffDrive']")
    for tag in ('left_joint', 'right_joint'):
        assert robot.find(f"joint[@name='{drive.findtext(tag)}']") is not None
    assert by_topic[drive.findtext('topic')]['direction'] == 'ROS_TO_GZ'
    assert by_topic[drive.findtext('odom_topic')]['ros_type_name'] == 'nav_msgs/msg/Odometry'
    assert by_topic[drive.findtext('tf_topic')]['ros_type_name'] == 'tf2_msgs/msg/TFMessage'
    assert drive.findtext('child_frame_id') in links


def test_world_supplies_sensor_systems_and_local_models():
    """The default world can resolve its models without the Classic database."""
    world = ET.parse(ROOT / 'ros_dd_gazebo/worlds/ros_dd.world').find('world')
    assert world.attrib['name'] == 'default'
    systems = {plugin.attrib['name'] for plugin in world.findall('plugin')}
    for system in ('Physics', 'UserCommands', 'SceneBroadcaster', 'Sensors', 'Imu'):
        assert f'gz::sim::systems::{system}' in systems
    for uri in world.findall('include/uri'):
        assert uri.text.startswith('model://')
        assert (ROOT / 'ros_dd_gazebo/models' / uri.text[8:] / 'model.sdf').is_file()


def test_saved_map_is_self_contained():
    """The installed navigation map references an included image."""
    maps = ROOT / 'ros_dd_navigation/maps'
    config = yaml.safe_load((maps / 'map.yaml').read_text())
    assert (maps / config['image']).is_file()
