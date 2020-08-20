#include <PyKinect/image.h>
#include <PyKinect/util.h>
#include <numpy/arrayobject.h>

#define pSelf ((ImageObject*)self)
#define m_image pSelf->image

/*
 *
 * Helper Functions
 *
 */

static inline PyObject* NumpyColorMJPG(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_COLOR_MJPG numpy serialization is not implemented");
	return NULL;
}

static inline PyObject* NumpyColorNV12(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_COLOR_NV12 numpy serialization is not implemented");
	return NULL;
}

static inline PyObject* NumpyColorYUY2(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_COLOR_YUY2 numpy serialization is not implemented");
	return NULL;
}

static inline PyObject* NumpyColorBGRA32(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_COLOR_BGRA32 numpy serialization is not implemented");
	return NULL;
}

static inline PyObject* NumpyDEPTH16(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_DEPTH16 numpy serialization is not implemented");
	return NULL;
}

static inline PyObject* NumpyIR16(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_IR16 numpy serialization is not implemented");
	return NULL;
}

static inline PyObject* NumpyCUSTOM8(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_CUSTOM8 numpy serialization is not implemented");
	return NULL;
}

static inline PyObject* NumpyCUSTOM16(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_CUSTOM16 numpy serialization is not implemented");
	return NULL;
}

static inline PyObject* NumpyCUSTOM(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	PyExc_SetString(PyExc_NotImplementedError, "K4A_IMAGE_FORMAT_CUSTOM numpy serialization is not implemented");
	return NULL;
}

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
	PyTypeObject* tp = Py_TYPE(self);
	
	k4a_image_release(((ImageObject*)self)->image);
	
	tp->tp_free(self);
	Py_DECREF(tp);
}

/*
 *
 * ImageObject Member Functions
 *
 */

PyObject* ImageObjectGetHeightPixels(PyObject* self, PyObject* args)
{
	int height = k4a_image_get_height_pixels(m_image);
	return PyLong_FromLong((long)height);
}

PyObject* ImageObjectGetWidthPixels(PyObject* self, PyObject* args)
{
	int width = k4a_image_get_width_pixels(m_image);
	return PyLong_FromLong((long)width);
}

PyObject* ImageObjectToNumpy(PyObject* self, PyObject* args)
{
	if (!PyArray_API)
		import_array();

	k4a_image_format_t fmt = k4a_image_get_format(m_image);
	switch (fmt)
	{
	case K4A_IMAGE_FORMAT_COLOR_MJPG:
		return NumpyColorMJPG(self, args);

	case K4A_IMAGE_FORMAT_COLOR_NV12:
		return NumpyColorNV12(self, args);

	case K4A_IMAGE_FORMAT_COLOR_YUY2:
		return NumpyColorYUY2(self, args);

	case K4A_IMAGE_FORMAT_COLOR_BGRA32:
		return NumpyColorBGRA32(self, args);

	case K4A_IMAGE_FORMAT_DEPTH16:
		return NumpyDEPTH16(self, args);

	case K4A_IMAGE_FORMAT_IR16:
		return NumpyIR16(self, args);

	case K4A_IMAGE_FORMAT_CUSTOM8:
		return NumpyCUSTOM8(self, args);

	case K4A_IMAGE_FORMAT_CUSTOM16:
		return NumpyCUSTOM16(self, args);

	case K4A_IMAGE_FORMAT_CUSTOM:
		return NumpyCUSTOM(self, args);

	default:
		PyErr_SetString(PyExc_ValueError, "k4a_image_get_format() returned an unrecognized k4a_image_format_t");
		return NULL;
	}
}
