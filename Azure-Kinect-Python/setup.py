import os
from distutils.core import setup, Extension
from distutils.sysconfig import get_python_inc, get_python_lib


_PyKinect = Extension(
    name="_PyKinect",
    sources=[
        "${CMAKE_CURRENT_SOURCE_DIR}/src/module.c",
        "${CMAKE_CURRENT_SOURCE_DIR}/src/device.c",
        "${CMAKE_CURRENT_SOURCE_DIR}/src/capture.c"
    ],
    include_dirs=[
        "${CMAKE_CURRENT_SOURCE_DIR}/include/",
        "${PY_ENV_PATH}/include/",
        "${K4A_PATH}/"
    ],
    library_dirs=[
        "${PY_ENV_PATH}/libs/",
        "${K4A_LIB}/"
    ],
    libraries=[
        "python38",
        "_PyKinect",
        "k4a"
    ],
    language="c"
)

shared_libs = os.listdir("./")
shared_libs = [e for e in shared_libs if e.split(".")[-1] == "dll"]

setup(
    name="PyKinect",
    version="1.0",
    description="Provides a C extension for Azure Kinect DK",
    author="Dario Morle",
    author_email="dario@ifiveo.com",
    ext_modules=[_PyKinect],
    install_requires=["numpy"],
    packages=["PyKinect"],
    package_dir={"PyKinect": "./PyKinect"},
    data_files = [(get_python_lib(), shared_libs)]
)
