#ifndef PYKINECT_DEVICE_CONFIG_H
#define PYKINECT_DEVICE_CONFIG_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <k4a/k4a.h>

typedef struct
{
    PyObject_HEAD
    k4a_device_configuration_t config;
}
DeviceConfigObject;

/*
 *
 * DeviceConfigObject Standard Function Prototypes
 *
 */

PyObject* DeviceConfigObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds);
int       DeviceConfigObjectInit(PyObject* self, PyObject* args, PyObject* kwds);
void      DeviceConfigObjectDealloc(PyObject* self);

/*
 *
 * DeviceConfigObject Member Function Prototypes
 *
 */

PyObject* DeviceConfigObjectSetColorFormat(PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetColorResolution(PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetDepthMode(PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetCameraFps(PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetSynchronizedImagesOnly(PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetDepthDelayOffColorUsec(PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetWritedSyncMode(PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetSubordinateDelayOffMaster(PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetDisableStreamingIndicator(PyObject* self, PyObject* args);

static PyMethodDef DeviceConfigObjectMethods[] = {
    {
        "set_color_format",
        DeviceConfigObjectSetColorFormat,
        METH_VARARGS,
        NULL
    },
    {
        "set_color_resolution",
        DeviceConfigObjectSetColorResolution,
        METH_VARARGS,
        NULL
    },
    {
        "set_depth_mode",
        DeviceConfigObjectSetDepthMode,
        METH_VARARGS,
        NULL
    },
    {
        "set_camera_fps",
        DeviceConfigObjectSetCameraFps,
        METH_VARARGS,
        NULL
    },
    {
        "set_synchronized_images_only",
        DeviceConfigObjectSetSynchronizedImagesOnly,
        METH_VARARGS,
        NULL
    },
    {
        "set_depth_delay_off_color_usec",
        DeviceConfigObjectSetDepthDelayOffColorUsec,
        METH_VARARGS,
        NULL
    },
    {
        "set_wired_sync_mode",
        DeviceConfigObjectSetWritedSyncMode,
        METH_VARARGS,
        NULL
    },
    {
        "set_subordinate_delay_off_master_usec",
        DeviceConfigObjectSetSubordinateDelayOffMaster,
        METH_VARARGS,
        NULL
    },
    {
        "set_disable_streaming_indicator",
        DeviceConfigObjectSetDisableStreamingIndicator,
        METH_VARARGS,
        NULL
    },
    {       // end of method list
        NULL,
        NULL,
        0,
        NULL
    }
};

/*
 *
 * DeviceConfigObject Member Variables
 *
 */

static PyTypeObject DeviceConfigObjectType = {
    PyObject_HEAD_INIT(NULL)
    .tp_name = "_PyKinect.DeviceConfig",
    .tp_basicsize = sizeof(DeviceConfigObject),
    .tp_itemsize = 0,
    .tp_doc = "Python interface for k4a device configuration",
    .tp_dealloc = DeviceConfigObjectDealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = DeviceConfigObjectMethods,
    .tp_new = DeviceConfigObjectNew,
    .tp_init = (initproc)DeviceConfigObjectInit
};

#endif
