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

PyObject* DeviceConfigObjectNew     (PyTypeObject* type, PyObject* args, PyObject* kwds);
int       DeviceConfigObjectInit    (PyObject* self, PyObject* args, PyObject* kwds);
void      DeviceConfigObjectDealloc (PyObject* self);
PyObject* DeviceConfigObjectRepr    (PyObject* self);

/*
 *
 * DeviceConfigObject Member Function Prototypes
 *
 */

PyObject* DeviceConfigObjectSetImageFormat               (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetImageFormat               (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetColorResolution           (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetColorResolution           (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetDepthMode                 (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetDepthMode                 (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetCameraFps                 (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetCameraFps                 (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetSynchronizedImagesOnly    (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetSynchronizedImagesOnly    (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetDepthDelayOffColorUsec    (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetDepthDelayOffColorUsec    (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetWritedSyncMode            (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetWritedSyncMode            (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetSubordinateDelayOffMaster (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetSubordinateDelayOffMaster (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectSetDisableStreamingIndicator (PyObject* self, PyObject* args);
PyObject* DeviceConfigObjectGetDisableStreamingIndicator (PyObject* self, PyObject* args);

static PyMethodDef DeviceConfigObjectMethods[] = {
    {
        "set_image_format",
        DeviceConfigObjectSetImageFormat,
        METH_VARARGS,
        NULL
    },
    {
        "get_image_format",
        DeviceConfigObjectGetImageFormat,
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
        "get_color_resolution",
        DeviceConfigObjectGetColorResolution,
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
        "get_depth_mode",
        DeviceConfigObjectGetDepthMode,
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
        "get_camera_fps",
        DeviceConfigObjectGetCameraFps,
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
        "get_synchronized_images_only",
        DeviceConfigObjectGetSynchronizedImagesOnly,
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
        "get_depth_delay_off_color_usec",
        DeviceConfigObjectGetDepthDelayOffColorUsec,
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
        "get_wired_sync_mode",
        DeviceConfigObjectGetWritedSyncMode,
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
        "get_subordinate_delay_off_master_usec",
        DeviceConfigObjectGetSubordinateDelayOffMaster,
        METH_VARARGS,
        NULL
    },
    {
        "set_disable_streaming_indicator",
        DeviceConfigObjectSetDisableStreamingIndicator,
        METH_VARARGS,
        NULL
    },
    {
        "get_disable_streaming_indicator",
        DeviceConfigObjectGetDisableStreamingIndicator,
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
    .tp_init = (initproc)DeviceConfigObjectInit,
    .tp_repr = DeviceConfigObjectRepr
};

#endif
