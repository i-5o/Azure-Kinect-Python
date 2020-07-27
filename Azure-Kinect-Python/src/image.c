#include <PyKinect/image.h>



/*
 *
 * Helper Functions
 *
 */

/*
 *
 * ImageObject Standard Functions
 *
 */

PyObject* ImageObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	ImageObject* self;

	self = (ImageObject*)type->tp_alloc(type, 0);
	if (!self)
	{
		PyErr_SetString(PyExc_MemoryError, "Unable to retrieve enough memory for PyKinect.Image");
		return NULL;
	}
	return (PyObject*)self;
}

int ImageObjectInit(PyObject* self, PyObject* args, PyObject* kwds)
{
	Py_ssize_t argNum = PyTuple_Size(args);
	if (argNum != 4)
	{
		char buf[64];
		sprintf(buf, "Expected 4 arguments, recieved %lu", argNum);
		PyErr_SetString(PyExc_ValueError, buf);
		return -1;
	}

	PyObject* pImgFmt = PyTuple_GetItem(args, 0);
	if (!pImgFmt)
	{
		PyErr_SetString(PyExc_RuntimeError, "Argument 0 is invalid");
		return -1;
	}
	if (!PyLong_Check(pImgFmt))
	{
		PyErr_SetString(PyExc_TypeError, "Expected argument 0 to be int");
		return -1;
	}
	k4a_image_format_t imgFmt = (k4a_image_format_t)PyLong_AsLong(pImgFmt);

	PyObject* pWidth = PyTuple_GetItem(args, 1);
	if (!pWidth)
	{
		PyErr_SetString(PyExc_RuntimeError, "Argument 1 is invalid");
		return -1;
	}
	if (!PyLong_Check(pWidth))
	{
		PyErr_SetString(PyExc_TypeError, "Expected argument 1 to be int");
		return -1;
	}
	int width = (int)PyLong_AsLong(pWidth);

	PyObject* pHeight = PyTuple_GetItem(args, 2);
	if (!pHeight)
	{
		PyErr_SetString(PyExc_RuntimeError, "Argument 2 is invalid");
		return -1;
	}
	if (!PyLong_Check(pHeight))
	{
		PyErr_SetString(PyExc_TypeError, "Expected argument 2 to be int");
		return -1;
	}
	int height = (int)PyLong_AsLong(pHeight);

	PyObject* pStride = PyTuple_GetItem(args, 3);
	if (!pStride)
	{
		PyErr_SetString(PyExc_RuntimeError, "Argument 3 is invalid");
		return -1;
	}
	if (!PyLong_Check(pStride))
	{
		PyErr_SetString(PyExc_TypeError, "Expected argument 3 to be int");
		return -1;
	}
	int stride = (int)PyLong_AsLong(pStride);

	if (K4A_FAILED(k4a_image_create(imgFmt, width, height, stride, ((ImageObject*)self)->image)))
	{
		PyErr_SetString(PyExc_SystemError, "k4a_image_create failed");
		return -1;
	}

	return 0;
}

void ImageObjectDealloc(PyObject* self)
{
	k4a_image_release(((ImageObject*)self)->image);
}

/*
 *
 * ImageObject Member Functions
 *
 */

PyObject* ImageObjectGetHeightPixels(PyObject* self, PyObject* args)
{
	int height = k4a_image_get_height_pixels(((ImageObject*)self)->image);
	return PyLong_FromLong((long)height);
}

PyObject* ImageObjectGetWidthPixels(PyObject* self, PyObject* args)
{
	int width = k4a_image_get_width_pixels(((ImageObject*)self)->image);
	return PyLong_FromLong((long)width);
}

PyObject* ImageObjectToNumpy(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}
