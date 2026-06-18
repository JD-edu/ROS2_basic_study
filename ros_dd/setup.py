from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'ros_dd'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
         # launch 파일 설치
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        # URDF 파일 설치
        (os.path.join('share', package_name, 'urdf'), glob('urdf/*.urdf')),
        # RViz 설정 파일 설치
        (os.path.join('share', package_name, 'rviz'), glob('rviz/*.rviz')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jd',
    maintainer_email='jd@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
        ],
    },
)
