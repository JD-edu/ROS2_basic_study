from setuptools import find_packages
from setuptools import setup

setup(
    name='cv_msg',
    version='0.0.0',
    packages=find_packages(
        include=('cv_msg', 'cv_msg.*')),
)
