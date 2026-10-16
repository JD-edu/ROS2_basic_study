"""Validate obstacle geometry and resources in the migrated table world."""
from pathlib import Path
import xml.etree.ElementTree as ET


WORLD = Path(__file__).resolve().parents[1] / 'worlds' / 'three_tables.world'


def test_tables_are_detectable_at_laser_height():
    """Keep the original poses and solid collisions for all three tables."""
    world = ET.parse(WORLD).find('world')
    assert world.attrib['name'] == 'three_tables'
    expected = {'table_1': (2, 1.5), 'table_2': (2, -1.5), 'table_3': (-2, 1.5)}
    tables = [m for m in world.findall('model') if m.attrib['name'].startswith('table_')]
    assert len(tables) == 3
    for table in tables:
        pose = list(map(float, table.findtext('pose').split()))
        assert tuple(pose[:2]) == expected[table.attrib['name']]
        size = list(map(float, table.findtext('link/collision/geometry/box/size').split()))
        assert size == [1.2, 0.8, 0.75]
        assert pose[2] - size[2] / 2 == 0
        assert pose[2] + size[2] / 2 > 0.235
        assert table.findtext('static') == 'true'


def test_world_has_walls_and_native_harmonic_systems():
    """The world runs without Classic's ground/sun model database."""
    world = ET.parse(WORLD).find('world')
    assert not world.findall('include')
    models = {m.attrib['name'] for m in world.findall('model')}
    assert models >= {'ground_plane', 'north', 'south', 'east', 'west'}
    systems = {p.attrib['name'] for p in world.findall('plugin')}
    for name in ('Physics', 'UserCommands', 'SceneBroadcaster', 'Sensors', 'Imu'):
        assert f'gz::sim::systems::{name}' in systems
