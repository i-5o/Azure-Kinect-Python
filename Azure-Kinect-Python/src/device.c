#include <PyKinect/device.h>
#include <PyKinect/capture.h>



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
	if (!self)
	{
		PyErr_SetString(PyExc_MemoryError, "Unable to retrieve enough memory for PyKinect.device");
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
	k4a_device_close(((DeviceObject*)self)->device);
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

	PyObject* pCap = PyObject_New(CaptureObject, &CaptureObjectType);
	if (!pCap)
	{
		PyErr_SetString(PyExc_MemoryError, "Unable to create a capture object");
		return NULL;
	}
	Py_IncRef(pCap);

	switch (k4a_device_get_capture(
		((DeviceObject*)self)->device,
		&((CaptureObject*)pCap)->capture,
		timeout_in_ms
	))
	{
	case K4A_WAIT_RESULT_SUCCEEDED:
		return pCap;
	case K4A_WAIT_RESULT_FAILED:
		Py_DecRef(pCap);
		PyErr_SetString(PyExc_SystemError, "Failed to get capture from camera");
		return NULL;
	case K4A_WAIT_RESULT_TIMEOUT:
		Py_DecRef(pCap);
		PyErr_SetString(PyExc_SystemError, "get_capture timed out when waiting for a capture");
		return NULL;
	default:
		Py_DecRef(pCap);
		PyErr_SetString(PyExc_SystemError, "get_capture resulted in an unknown error");
		return NULL;
	}
}

PyObject* DeviceObjectStartCameras(PyObject* self, PyObject* args)
{
	Py_ssize_t argNum = PyTuple_Size(args);
	if (argNum != 9)
	{
		char buf[64];
		sprintf(buf, "Expected 9 arguments, recieved %u", (uint32_t)argNum);
		PyErr_SetString(PyExc_ValueError, buf);
		return NULL;
	}

	// color_format
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
	k4a_image_format_t colorFmt = (k4a_image_format_t)PyLong_AsLong(pColorFmt);

	// color_resolution
	PyObject* pColorRes = PyTuple_GetItem(args, 1);
	if (!pColorRes)
	{
		PyErr_SetString(PyExc_RuntimeError, "color_resolution arg was invalid");
		return NULL;
	}
	if (!PyLong_Check(pColorRes))
	{
		PyErr_SetString(PyExc_TypeError, "color_resolution arg must have type int");
		return NULL;
	}
	k4a_color_resolution_t colorRes = (k4a_color_resolution_t)PyLong_AsLong(pColorRes);

	// depth_mode
	PyObject* pDepthMd = PyTuple_GetItem(args, 2);
	if (!pDepthMd)
	{
		PyErr_SetString(PyExc_RuntimeError, "depth_mode arg was invalid");
		return NULL;
	}
	if (!PyLong_Check(pDepthMd))
	{
		PyErr_SetString(PyExc_TypeError, "depth_mode arg must have type int");
		return NULL;
	}
	k4a_depth_mode_t depthMd = (k4a_depth_mode_t)PyLong_AsLong(pDepthMd);

	// camera_fps
	PyObject* pFps = PyTuple_GetItem(args, 3);
	if (!pFps)
	{
		PyErr_SetString(PyExc_RuntimeError, "camera_fps arg was invalid");
		return NULL;
	}
	if (!PyLong_Check(pFps))
	{
		PyErr_SetString(PyExc_TypeError, "camera_fps arg must have type int");
		return NULL;
	}
	k4a_fps_t fps = (k4a_fps_t)PyLong_AsLong(pFps);

	// synchronized_images_only
	PyObject* pSyncImgF = PyTuple_GetItem(args, 4);
	if (!pSyncImgF)
	{
		PyErr_SetString(PyExc_RuntimeError, "synchronized_images_only arg was invalid");
		return NULL;
	}
	bool syncImgF = PyObject_IsTrue(pSyncImgF);

	// depth_delay_off_color_usec
	PyObject* pDepthDelay = PyTuple_GetItem(args, 5);
	if (!pDepthDelay)
	{
		PyErr_SetString(PyExc_RuntimeError, "depth_delay_off_color_usec arg was invalid");
		return NULL;
	}
	if (!PyLong_Check(pDepthDelay))
	{
		PyErr_SetString(PyExc_TypeError, "depth_delay_off_color_usec arg must have type int");
		return NULL;
	}
	int32_t depthDelay = (int32_t)PyLong_AsLong(pDepthDelay);

	// wired_sync_mode
	PyObject* pWiredSyncMd = PyTuple_GetItem(args, 6);
	if (!pWiredSyncMd)
	{
		PyErr_SetString(PyExc_RuntimeError, "wired_sync_mode arg was invalid");
		return NULL;
	}
	if (!PyLong_Check(pWiredSyncMd))
	{
		PyErr_SetString(PyExc_TypeError, "wired_sync_mode arg must have type int");
		return NULL;
	}
	k4a_wired_sync_mode_t wiredSyncMd = (k4a_wired_sync_mode_t)PyLong_AsLong(pWiredSyncMd);

	// subordinate_delay_off_master_usec
	PyObject* pSubDelay = PyTuple_GetItem(args, 7);
	if (!pSubDelay)
	{
		PyErr_SetString(PyExc_RuntimeError, "subordinate_delay_off_master_usec arg was invalid");
		return NULL;
	}
	if (!PyLong_Check(pSubDelay))
	{
		PyErr_SetString(PyExc_TypeError, "subordinate_delay_off_master_usec arg must have type int");
		return NULL;
	}
	uint32_t subDelay = (uint32_t)PyLong_AsLong(pSubDelay);

	// disable_streaming_indicator
	PyObject* pStreamIndF = PyTuple_GetItem(args, 8);
	if (!pStreamIndF)
	{
		PyErr_SetString(PyExc_RuntimeError, "disable_streaming_indicator arg was invalid");
		return NULL;
	}
	bool streamIndF = PyObject_IsTrue(pStreamIndF);

	k4a_device_configuration_t config =
	{
		colorFmt,
		colorRes,
		depthMd,
		fps,
		syncImgF,
		depthDelay,
		wiredSyncMd,
		subDelay,
		streamIndF
	};

	if (K4A_SUCCEEDED(k4a_device_start_cameras(((DeviceObject*)self)->device, &config)))
		Py_RETURN_TRUE;

	Py_RETURN_FALSE;
}

PyObject* DeviceObjectStopCameras(PyObject* self, PyObject* args)
{
	Py_RETURN_NOTIMPLEMENTED;
}
