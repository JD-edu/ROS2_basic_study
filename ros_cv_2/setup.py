from setuptools import find_packages, setup

package_name = 'ros_cv_2'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml', 'README.md']),
        ('share/' + package_name + '/launch', [
            'launch/dual_cameras.launch.py',
            'launch/rgbd_cameras.launch.py',
        ]),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jd',
    maintainer_email='jd@todo.todo',
    description='Low-latency streaming for the second camera',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'cam_pub = ros_cv_2.cam_pub:main',
            'cam_sub = ros_cv_2.cam_sub:main',
        ],
    },
)
