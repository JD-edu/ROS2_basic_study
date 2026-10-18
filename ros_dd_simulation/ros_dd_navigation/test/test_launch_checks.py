"""Validate saved-map inputs before starting the simulation."""
import pytest
import yaml

from ros_dd_navigation.launch_checks import validate_map_file


def test_relative_image_is_relative_to_yaml(tmp_path, monkeypatch):
    directory = tmp_path / 'saved map'
    directory.mkdir()
    (directory / 'room.pgm').write_bytes(b'P5\n1 1\n255\n\xff')
    path = directory / 'room.yaml'
    path.write_text(yaml.safe_dump({'image': 'room.pgm'}))
    elsewhere = tmp_path / 'elsewhere'
    elsewhere.mkdir()
    monkeypatch.chdir(elsewhere)
    assert validate_map_file(str(path)) == str(path.resolve())


def test_missing_map_is_rejected(tmp_path):
    with pytest.raises(RuntimeError, match='Map YAML file does not exist'):
        validate_map_file(str(tmp_path / 'missing.yaml'))


def test_missing_image_is_rejected(tmp_path):
    path = tmp_path / 'map.yaml'
    path.write_text('image: missing.pgm\n')
    with pytest.raises(RuntimeError, match='Map image does not exist'):
        validate_map_file(str(path))


@pytest.mark.parametrize('content', ['[]', 'null', 'image: 123', '{}'])
def test_invalid_yaml_is_rejected(tmp_path, content):
    path = tmp_path / 'map.yaml'
    path.write_text(content)
    with pytest.raises(RuntimeError, match='Map YAML must contain an image path'):
        validate_map_file(str(path))
