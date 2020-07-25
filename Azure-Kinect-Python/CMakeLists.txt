include_directories("include")

# linking python and numpy
set(PY_ENV_NAME "PyKinect")

if (WIN32)
	set(PY_ENV_PATH "C:$ENV{HOMEPATH}/anaconda3/envs/${PY_ENV_NAME}")
endif (WIN32)
if (UNIX)
	set(PY_ENV_PATH "$ENV{PYTHONPATH}")
endif(UNIX)

string(REPLACE "\\" "/" PY_ENV_PATH ${PY_ENV_PATH})

set(PY_ENV_NP_PATH "${PY_ENV_PATH}/Lib/site-packages/numpy/core")

include_directories("${PY_ENV_PATH}/include")
include_directories("${PY_ENV_NP_PATH}/include")

link_directories("${PY_ENV_PATH}")
link_directories("${PY_ENV_PATH}/libs/")

add_library(
	PyKinect SHARED
	"src/module.c"
	"src/device.c"
	"include/PyKinect/device.h"
)

# linking k4a
#find_package(k4a CONFIG REQUIRED)
#target_link_libraries(PyKinect PRIVATE k4a::k4a)

find_package(k4arecord CONFIG REQUIRED)
target_link_libraries(PyKinect PRIVATE k4a::k4arecord)

find_path(K4A_PATH k4a/k4a.h REQUIRED)
string(REPLACE "\\" "/" K4A_PATH ${K4A_PATH})
target_link_directories(PyKinect PUBLIC ${K4A_PATH})

find_library(K4A_LIB k4a REQUIRED)
string(REPLACE "\\" "/" K4A_LIB ${K4A_LIB})
target_link_libraries(PyKinect PRIVATE ${K4A_LIB})

string(REPLACE "/k4a.lib" "" K4A_LIB ${K4A_LIB})

target_link_libraries(PyKinect PUBLIC "${PY_ENV_PATH}/libs/python38.lib")

configure_file("setup.py" "setup.py")
