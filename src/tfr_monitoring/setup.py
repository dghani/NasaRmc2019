from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

t = generate_distutils_setup(
    packages=['tfr_monitoring'],
    package_dir={'': ''}
)

setup(**t)
