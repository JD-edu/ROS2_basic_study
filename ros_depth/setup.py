from setuptools import find_packages, setup


package_name = 'ros_depth'


setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        (
            'share/ament_index/resource_index/packages',
            ['resource/' + package_name],
        ),
        ('share/' + package_name, ['package.xml', 'README.md']),
        (
            'share/' + package_name + '/launch',
            ['launch/camera_receivers.launch.py'],
        ),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jd',
    maintainer_email='jd@todo.todo',
    description='Low-latency subscriber for 16UC1 depth images',
    license='MIT',
    entry_points={
        'console_scripts': [
            'depth_sub = ros_depth.depth_sub:main',
        ],
    },
)
