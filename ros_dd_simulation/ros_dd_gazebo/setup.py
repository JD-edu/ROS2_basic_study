from setuptools import find_packages, setup
import os 
from glob import glob

package_name = 'ros_dd_gazebo'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.py'))),
        # URDF 파일 설치
        (os.path.join('share', package_name, 'urdf'), glob(os.path.join('urdf', '*'))),
        # 월드 파일 설치
        (os.path.join('share', package_name, 'worlds'), glob(os.path.join('worlds', '*.world'))),
        #(os.path.join('share', package_name, 'urdf'), glob(os.path.join('models', '*.sdf'))),
        # 모델 파일 설치 (이 부분이 중요합니다)
        #(os.path.join('share', package_name, 'models', 'cube'), glob('models/cube/*')),
        (os.path.join('share', package_name, 'models', 'hexa'), 
        glob('models/hexa/*.config') + glob('models/hexa/*.sdf')), 
        # for robot 
        (os.path.join('share', package_name, 'models', 'robot'), 
        glob('models/robot/*.config') + glob('models/robot/*.sdf')), 
         
        # 2. meshes 폴더 내부 파일 복사 (가장 중요!)
        # install/share/ros_empty/models/cube/meshes/ 경로로 dae 파일을 복사
        (os.path.join('share', package_name, 'models', 'hexa', 'meshes'), 
        glob('models/hexa/meshes/*')), 
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
