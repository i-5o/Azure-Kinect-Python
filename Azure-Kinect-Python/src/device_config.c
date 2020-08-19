#include <PyKinect/device_config.h>

#define pSelf ((DeviceConfigObject*)self)
#define m_cfg  pSelf->config

 /*
  *
  * DeviceObject Standard Functions
  *
  */

PyObject* DeviceObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	DeviceConfigObject* self;

	self = (DeviceConfigObject*)type->tp_alloc(type, 0);
	if (!self)
	{
		PyErr_SetString(PyExc_MemoryError, "Unable to retrieve enough memory for PyKinect.Device");
		return NULL;
	}
	return (PyObject*)self;
}

int DeviceObjectInit(PyObject* self, PyObject* args, PyObject* kwds)
{
	m_cfg = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;

	return 0;
}

void DeviceObjectDealloc(PyObject* self)
{
	PyTypeObject* tp = Py_TYPE(self);
	tp->tp_free(self);
	Py_DECREF(tp);
}

/*
 *
 * DeviceObject Member Functions
 *
 */

PyObject* DeviceConfigObjectSetColorFormat(PyObject* self, PyObject* args)
{
	PyObject* pColorFmt = PyTuple_GetItem(args, 0);
	if (!pColorFmt)
	{
		PyErr_SetString(PyExc_RuntimeError, "color_format arg was invalid");
		return NULL;
	}
	if (!PyLong_Check(pColorFmt))
	{
		PyErr_SetString(PyExc_TypeError, "color_format arg must have type int");
		return NULL;
	}
	m_cfg.color_format = (k4a_image_format_t)PyLong_AsLong(pColorFmt);
	Py_RETURN_NONE;
}

PyObject* DeviceConfigObjectSetColorFormat(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetColorFormat(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetColorResolution(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetColorResolution(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetDepthMode(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetDepthMode(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetCameraFps(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetCameraFps(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetSynchronizedImagesOnly(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetSynchronizedImagesOnly(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetDepthDelayOffColorUsec(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetDepthDelayOffColorUsec(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetWritedSyncMode(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetWritedSyncMode(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetSubordinateDelayOffMaster(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetSubordinateDelayOffMaster(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetDisableStreamingIndicator(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetDisableStreamingIndicator(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}
