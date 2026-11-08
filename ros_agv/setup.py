from setuptools import find_packages, setup

package_name = 'ros_agv'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name, ['README.md']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jd',
    maintainer_email='jd@todo.todo',
    description='Two-wheel differential-drive Arduino bring-up',
    license='MIT',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'ros_agv = ros_agv.ros_agv_2:main',
            'ros_agv_2 = ros_agv.ros_agv_2:main',
        ],
    },
)
