#ifndef PYKINECT_DEVICE_H
#define PYKINECT_DEVICE_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <k4a/k4a.h>

typedef struct
{
    PyObject_HEAD
    k4a_device_t device;
}
DeviceObject;

/*
 *
 * DeviceObject Standard Function Prototypes
 *
 */

PyObject* DeviceObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds);
int       DeviceObjectInit(PyObject* self, PyObject* args, PyObject* kwds);
void      DeviceObjectDealloc(PyObject* self);

/*
 *
 * DeviceObject Member Function Prototypes
 *
 */

PyObject* DeviceObjectGetCapture(PyObject* self, PyObject* args);
PyObject* DeviceObjectStartCameras(PyObject* self, PyObject* args);
PyObject* DeviceObjectStopCameras(PyObject* self, PyObject* args);

static PyMethodDef DeviceObjectMethods[] = {
    {
        "get_capture",
        DeviceObjectGetCapture,
        METH_VARARGS,
        NULL
    },
    {
        "start_cameras",
        DeviceObjectStartCameras,
        METH_VARARGS,
        NULL
    },
    {
        "stop_cameras",
        DeviceObjectStopCameras,
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
 * DeviceObject Member Variables
 *
 */

static PyTypeObject DeviceObjectType = {
    PyObject_HEAD_INIT(NULL)
    .tp_name = "PyKinect.Device",
    .tp_basicsize = sizeof(DeviceObject),
    .tp_itemsize = 0,
    .tp_doc = "Python interface for k4a devices",
    .tp_dealloc = DeviceObjectDealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = DeviceObjectMethods,
    .tp_new = DeviceObjectNew,
    .tp_init = (initproc)DeviceObjectInit
};

#endif
