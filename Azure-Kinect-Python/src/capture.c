#include <PyKinect/capture.h>
#include <PyKinect/image.h>



/*
 *
 * Helper Functions
 *
 */

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
	k4a_capture_release(((CaptureObject*)self)->capture);
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
	{
		PyErr_SetString(PyExc_MemoryError, "Unable to allocate memory for Image object");
		return NULL;
	}
	Py_DECREF(PyObject_Dir(pImage));

	((ImageObject*)pImage)->image = k4a_capture_get_color_image(((CaptureObject*)self)->capture);
	return pImage;
}
