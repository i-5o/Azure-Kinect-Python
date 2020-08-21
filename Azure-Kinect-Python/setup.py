import os
from distutils.core import setup, Extension
from distutils.sysconfig import get_python_inc, get_python_lib

source_files = os.listdir("${CMAKE_CURRENT_SOURCE_DIR}/src/")
source_files = ["${CMAKE_CURRENT_SOURCE_DIR}/src/" + e for e in source_files if e.split(".")[-1] == "c"]

_PyKinect = Extension(
    name="_PyKinect",
    sources=source_files,
    include_dirs=[
        "${CMAKE_CURRENT_SOURCE_DIR}/include/",
        "${PY_ENV_PATH}/include/",
        "${PY_ENV_NP_PATH}/include/",
        "${K4A_PATH}/"
    ],
    library_dirs=[
        "${PY_ENV_PATH}/libs/",
        "${K4A_LIB}/"
    ],
    libraries=[
        "python38",
        "k4a"
    ],
    language="c"
)

shared_libs = os.listdir("./")
shared_libs = [e for e in shared_libs if e.split(".")[-1] == "dll"]

setup(
    name="PyKinect",
    version="0.0.1",
    description="Provides a C extension for Azure Kinect DK",
    author="Dario Morle",
    author_email="dario@ifiveo.com",
    ext_modules=[_PyKinect],
    install_requires=["numpy"],
    packages=["PyKinect"],
    package_dir={"PyKinect": "./PyKinect"},
    data_files = [(get_python_lib(), shared_libs)]
)
