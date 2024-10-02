import glob
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir
from setuptools import setup

ext_modules = [
    Pybind11Extension('breakout', sorted(glob.glob('src/*.cpp')))
]

setup(
    ext_modules=ext_modules,
    cmdclass={'build_ext': build_ext}
)
