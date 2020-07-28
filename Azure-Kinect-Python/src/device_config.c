#include <PyKinect/device_config.h>



/*
 *
 * Helper Functions
 *
 */

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
	((DeviceConfigObject*)self)->config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;

	return 0;
}

void DeviceObjectDealloc(PyObject* self)
{
}

/*
 *
 * DeviceObject Member Functions
 *
 */

PyObject* DeviceConfigObjectSetColorFormat(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetColorResolution(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetDepthMode(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetCameraFps(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetSynchronizedImagesOnly(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetDepthDelayOffColorUsec(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetWritedSyncMode(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetSubordinateDelayOffMaster(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectSetDisableStreamingIndicator(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}
