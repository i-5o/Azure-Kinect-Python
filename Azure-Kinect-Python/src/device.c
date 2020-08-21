#include <PyKinect/device.h>
#include <PyKinect/capture.h>
#include <PyKinect/device_config.h>
#include <PyKinect/util.h>

#define pSelf       ((DeviceObject*)self)
#define m_device    pSelf->device

/*
 *
 * DeviceObject Standard Functions
 *
 */

PyObject* DeviceObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	DeviceObject* self;

	self = (DeviceObject*)type->tp_alloc(type, 0);
	if (!self)
	{
		PyErr_SetString(PyExc_MemoryError, "Unable to retrieve enough memory for PyKinect.Device");
		return NULL;
	}
	return (PyObject*)self;
}

int DeviceObjectInit(PyObject* self, PyObject* args, PyObject* kwds)
{
	if (PyTuple_Size(args) != 1)
	{
		PyErr_SetString(PyExc_ValueError, "A camera index was not provided");
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
	PyTypeObject* tp = Py_TYPE(self);

	k4a_device_close(((DeviceObject*)self)->device);

	tp->tp_free(self);
	Py_DECREF(tp);
}

/*
 *
 * DeviceObject Member Functions
 *
 */

PyObject* DeviceObjectGetCapture(PyObject* self, PyObject* args)
{
	Py_ssize_t argNum = PyTuple_Size(args);
	int32_t timeout_in_ms;
	char buf[64];
	switch (argNum)
	{
	case 0:
		timeout_in_ms = K4A_WAIT_INFINITE;
		break;
	case 1:
	{
		PyObject* pTimeout = PyTuple_GetItem(args, 0);
		if (!pTimeout)
		{
			PyErr_SetString(PyExc_RuntimeError, "Invalid timeout argument");
			return NULL;
		}
		if (!PyLong_Check(pTimeout))
		{
			PyErr_SetString(PyExc_TypeError, "A timeout for get_capture must be specified as an integer");
			return NULL;
		}
		timeout_in_ms = (int32_t)PyLong_AsLong(pTimeout);
		break;
	}
	default:
		sprintf(buf, "get_capture expected either 0 or 1 argument, recieved %d", (int)argNum);
		PyErr_SetString(PyExc_ValueError, buf);
		return NULL;
	}

	CaptureObject* pCap = PyObject_New(CaptureObject, &CaptureObjectType);
	if (!pCap)
	{
		PyErr_SetString(PyExc_MemoryError, "Unable to create a capture object");
		return NULL;
	}
	Py_DECREF(PyObject_Dir((PyObject*)pCap));

	switch (k4a_device_get_capture(
		m_device,
		&pCap->capture,
		timeout_in_ms
	))
	{
	case K4A_WAIT_RESULT_SUCCEEDED:
		return (PyObject*)pCap;
	case K4A_WAIT_RESULT_FAILED:
		Py_DecRef((PyObject*)pCap);
		PyErr_SetString(PyExc_SystemError, "Failed to get capture from camera");
		return NULL;
	case K4A_WAIT_RESULT_TIMEOUT:
		Py_DecRef((PyObject*)pCap);
		PyErr_SetString(PyExc_SystemError, "get_capture timed out when waiting for a capture");
		return NULL;
	default:
		Py_DecRef((PyObject*)pCap);
		PyErr_SetString(PyExc_SystemError, "get_capture resulted in an unknown error");
		return NULL;
	}
}

PyObject* DeviceObjectStartCameras(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pPyKinectMod = PyImport_ImportModule("_PyKinect");
	if (!pPyKinectMod)
		return NULL;

	PyObject* pPyDeviceConfig = PyObject_GetAttrString(pPyKinectMod, "DeviceConfig");
	Py_DECREF(pPyKinectMod);
	if (!pPyDeviceConfig)
		return NULL;

	PyObject* pArg = PyTuple_GetItem(args, 0);

	int ret = PyObject_IsInstance(pArg, pPyDeviceConfig);
	Py_DECREF(pPyDeviceConfig);
	if (ret == -1)
		return NULL;
	if (!ret)
	{
		PyErr_SetString(PyExc_TypeError, "Argument 0 was not of type DeviceConfig");
		return NULL;
	}

	if (!K4A_SUCCEEDED(k4a_device_start_cameras(m_device, &((DeviceConfigObject*)pArg)->config)))
	{
		PyErr_SetString(PyExc_SystemError, "k4a_device_start_cameras() returned K4A_RESULT_FAILED - Unable to start camera");
		return NULL;
	}

	Py_RETURN_NONE;
}

PyObject* DeviceObjectStopCameras(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	k4a_device_stop_cameras(m_device);
	Py_RETURN_NONE;
}
