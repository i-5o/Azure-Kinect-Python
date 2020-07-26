#ifndef PYKINECT_CAPTURE_H
#define PYKINECT_CAPTURE_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <k4a/k4a.h>

typedef struct
{
    PyObject_HEAD
    k4a_capture_t capture;
}
CaptureObject;

/*
 *
 * CaptureObject Standard Function Prototypes
 *
 */

PyObject* CaptureObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds);
int       CaptureObjectInit(PyObject* self, PyObject* args, PyObject* kwds);
void      CaptureObjectDealloc(PyObject* self);

/*
 *
 * CaptureObject Member Function Prototypes
 *
 */

PyObject* CaptureObjectGetColorImage(PyObject* self, PyObject* args);

static PyMethodDef CaptureObjectMethods[] = {
    {
        "get_color_image",
        CaptureObjectGetColorImage,
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
 * CaptureObject Member Variables
 *
 */

static PyTypeObject CaptureObjectType = {
    PyObject_HEAD_INIT(NULL)
    .tp_name = "PyKinect.Capture",
    .tp_basicsize = sizeof(CaptureObject),
    .tp_itemsize = 0,
    .tp_doc = "Python interface for k4a captures",
    .tp_dealloc = CaptureObjectDealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = CaptureObjectMethods,
    .tp_new = CaptureObjectNew,
    .tp_init = (initproc)CaptureObjectInit
};

#endif
