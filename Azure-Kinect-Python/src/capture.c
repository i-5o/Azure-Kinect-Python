#include <PyKinect/capture.h>
#include <PyKinect/image.h>

#define pSelf     ((CaptureObject*)self)
#define m_capture pSelf->capture

/*
 *
 * CaptureObject Standard Functions
 *
 */

PyObject* CaptureObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	CaptureObject* self;

	self = (CaptureObject*)type->tp_alloc(type, 0);
	if (!self)
	{
		PyErr_SetString(PyExc_MemoryError, "Unable to retrieve enough memory for PyKinect.Capture");
		return NULL;
	}
	return (PyObject*)self;
}

int CaptureObjectInit(PyObject* self, PyObject* args, PyObject* kwds)
{
	if (K4A_FAILED(k4a_capture_create(&((CaptureObject*)self)->capture)))
	{
		PyErr_SetString(PyExc_SystemError, "k4a_capture_create failed");
		return -1;
	}
	return 0;
}

void CaptureObjectDealloc(PyObject* self)
{
	PyTypeObject* tp = Py_TYPE(self);

	k4a_capture_release(((CaptureObject*)self)->capture);

	tp->tp_free(self);
	Py_DECREF(tp);
}

/*
 *
 * CaptureObject Member Functions
 *
 */

PyObject* CaptureObjectGetColorImage(PyObject* self, PyObject* args)
{
	PyObject* pImage = PyObject_New(ImageObject, &ImageObjectType);
	if (!pImage)
		return NULL;

	Py_DECREF(PyObject_Dir(pImage));

	((ImageObject*)pImage)->image = k4a_capture_get_color_image(m_capture);
	return pImage;
}

PyObject* CaptureObjectGetDepthImage(PyObject* self, PyObject* args)
{
	PyObject* pImage = PyObject_New(ImageObject, &ImageObjectType);
	if (!pImage)
		return NULL;

	Py_DECREF(PyObject_Dir(pImage));

	((ImageObject*)pImage)->image = k4a_capture_get_depth_image(m_capture);
	return pImage;
}

PyObject* CaptureObjectGetIRImage(PyObject* self, PyObject* args)
{
	PyObject* pImage = PyObject_New(ImageObject, &ImageObjectType);
	if (!pImage)
		return NULL;

	Py_DECREF(PyObject_Dir(pImage));

	((ImageObject*)pImage)->image = k4a_capture_get_ir_image(m_capture);
	return pImage;
}
