#include <PyKinect/device.h>



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
	DeviceObject* self;

	self = (DeviceObject*)type->tp_alloc(type, 0);
	return (PyObject*)self;
}

int DeviceObjectInit(PyObject* self, PyObject* args, PyObject* kwds)
{
	if (PyTuple_Size(args) != 1)
	{
		PyErr_SetString(PyExc_ValueError, "A camera index was not provided!");
		return -1;
	}

	PyObject* pIdx = PyTuple_GetItem(args, 0);
	if (!PyLong_Check(pIdx))
	{
		PyErr_SetString(PyExc_TypeError, "Expected argument 0 to be int");
		return -1;
	}
	long dIdx = PyLong_AsLong(pIdx);

	if (K4A_FAILED(k4a_device_open(dIdx, &((DeviceObject*)self)->device)))
	{
		char buf[64];
		sprintf(buf, "k4a_device_open failed on device %ld", dIdx);
		PyErr_SetString(PyExc_SystemError, buf);
		return -1;
	}

	return 0;
}

void DeviceObjectDealloc(PyObject* self)
{
	k4a_device_close(((DeviceObject*)self)->device);
}

/*
 *
 * DeviceObject Member Functions
 *
 */

PyObject* DeviceObjectGetCapture(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}
