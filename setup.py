import glob
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir
from setuptools import setup

with open('README.md', 'r', encoding='utf-8') as fh:
    long_description = fh.read()

ext_modules = [
    Pybind11Extension('breakout', sorted(glob.glob('src/*.cpp')))
]

setup(
    name='breakout-detection',
    version='0.1.0',
    description='Breakout detection for Python',
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/ankane/breakout-python',
    author='Andrew Kane',
    author_email='andrew@ankane.org',
    license='GPL-2.0-or-later',
    ext_modules=ext_modules,
    extras_require={'test': 'pytest'},
    cmdclass={'build_ext': build_ext},
    python_requires='>=3.6',
    zip_safe=False
)
