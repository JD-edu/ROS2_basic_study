from glob import glob

from setuptools import find_packages, setup

package_name = 'diy_lidar'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml', 'README.md']),
        ('share/' + package_name + '/launch', glob('launch/*.launch.py')),
        ('share/' + package_name + '/rviz', glob('rviz/*.rviz')),
        ('share/' + package_name + '/arduino/lidar_simulator',
            ['arduino/lidar_simulator/lidar_simulator.ino']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jdedu',
    maintainer_email='jdedu.kr@gmail.com',
    description='Arduino simulated lidar bridge and Tkinter viewer',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'lidar_bridge = diy_lidar.lidar_bridge:main',
            'lidar_viewer = diy_lidar.lidar_viewer:main',
        ],
    },
)
