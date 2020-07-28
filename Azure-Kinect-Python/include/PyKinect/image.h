#ifndef PYKINECT_IMAGE_H
#define PYKINECT_IMAGE_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <k4a/k4a.h>

typedef struct
{
    PyObject_HEAD
    k4a_image_t image;
}
ImageObject;

/*
 *
 * ImageObject Standard Function Prototypes
 *
 */

PyObject* ImageObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds);
int       ImageObjectInit(PyObject* self, PyObject* args, PyObject* kwds);
void      ImageObjectDealloc(PyObject* self);

/*
 *
 * ImageObject Member Function Prototypes
 *
 */

PyObject* ImageObjectGetHeightPixels(PyObject* self, PyObject* args);
PyObject* ImageObjectGetWidthPixels(PyObject* self, PyObject* args);
PyObject* ImageObjectToNumpy(PyObject* self, PyObject* args);

static PyMethodDef ImageObjectMethods[] = {
    {
        "get_height_pixels",
        ImageObjectGetHeightPixels,
        METH_VARARGS,
        NULL
    },
    {
        "get_width_pixels",
        ImageObjectGetWidthPixels,
        METH_VARARGS,
        NULL
    },
    {
        "to_numpy",
        ImageObjectToNumpy,
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
 * ImageObject Member Variables
 *
 */

static PyTypeObject ImageObjectType = {
    PyObject_HEAD_INIT(NULL)
    .tp_name = "_PyKinect.Image",
    .tp_basicsize = sizeof(ImageObject),
    .tp_itemsize = 0,
    .tp_doc = "Python interface for k4a images",
    .tp_dealloc = ImageObjectDealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = ImageObjectMethods,
    .tp_new = ImageObjectNew,
    .tp_init = (initproc)ImageObjectInit
};

#endif
