#include <PyKinect/device_config.h>
#include <PyKinect/util.h>

#define pSelf     ((DeviceConfigObject*)self)
#define m_cfg     pSelf->config

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
	CHECK_ARGNUM(args, 1);

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

PyObject* DeviceConfigObjectGetColorFormat(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	return PyLong_FromLong(m_cfg.color_format);
}

PyObject* DeviceConfigObjectSetColorResolution(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pColorRes = PyTuple_GetItem(args, 0);
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
	m_cfg.color_resolution = (k4a_color_resolution_t)PyLong_AsLong(pColorRes);

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject* DeviceConfigObjectGetColorResolution(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	return PyLong_FromLong(m_cfg.color_resolution);
}

PyObject* DeviceConfigObjectSetDepthMode(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pDepthMd = PyTuple_GetItem(args, 0);
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
	m_cfg.depth_mode = (k4a_depth_mode_t)PyLong_AsLong(pDepthMd);

	Py_RETURN_NONE;
}

PyObject* DeviceConfigObjectGetDepthMode(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	return PyLong_FromLong(m_cfg.depth_mode);
}

PyObject* DeviceConfigObjectSetCameraFps(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pFps = PyTuple_GetItem(args, 0);
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
	m_cfg.camera_fps = (k4a_fps_t)PyLong_AsLong(pFps);

	Py_RETURN_NONE;
}

PyObject* DeviceConfigObjectGetCameraFps(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	return PyLong_FromLong(m_cfg.camera_fps);
}

PyObject* DeviceConfigObjectSetSynchronizedImagesOnly(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pSyncImgF = PyTuple_GetItem(args, 0);
	if (!pSyncImgF)
	{
		PyErr_SetString(PyExc_RuntimeError, "synchronized_images_only arg was invalid");
		return NULL;
	}
	m_cfg.synchronized_images_only = PyObject_IsTrue(pSyncImgF);

	Py_RETURN_NONE;
}

PyObject* DeviceConfigObjectGetSynchronizedImagesOnly(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	if (m_cfg.synchronized_images_only)
		Py_RETURN_TRUE;
	Py_RETURN_FALSE;
}

PyObject* DeviceConfigObjectSetDepthDelayOffColorUsec(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pDepthDelay = PyTuple_GetItem(args, 0);
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
	m_cfg.depth_delay_off_color_usec = (int32_t)PyLong_AsLong(pDepthDelay);

	Py_RETURN_NONE;
}

PyObject* DeviceConfigObjectGetDepthDelayOffColorUsec(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	return PyLong_FromLong(m_cfg.depth_delay_off_color_usec);
}

PyObject* DeviceConfigObjectSetWritedSyncMode(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pWiredSyncMd = PyTuple_GetItem(args, 0);
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
	m_cfg.wired_sync_mode = (k4a_wired_sync_mode_t)PyLong_AsLong(pWiredSyncMd);

	Py_RETURN_NONE;
}

PyObject* DeviceConfigObjectGetWritedSyncMode(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	return PyLong_FromLong(m_cfg.wired_sync_mode);
}

PyObject* DeviceConfigObjectSetSubordinateDelayOffMaster(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pSubDelay = PyTuple_GetItem(args, 0);
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
	m_cfg.subordinate_delay_off_master_usec = (uint32_t)PyLong_AsLong(pSubDelay);

	Py_RETURN_NONE;
}

PyObject* DeviceConfigObjectGetSubordinateDelayOffMaster(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	return PyLong_FromLong(m_cfg.subordinate_delay_off_master_usec);
}

PyObject* DeviceConfigObjectSetDisableStreamingIndicator(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 1);

	PyObject* pStreamIndF = PyTuple_GetItem(args, 8);
	if (!pStreamIndF)
	{
		PyErr_SetString(PyExc_RuntimeError, "disable_streaming_indicator arg was invalid");
		return NULL;
	}
	m_cfg.disable_streaming_indicator = PyObject_IsTrue(pStreamIndF);

	Py_RETURN_NONE;
}

PyObject* DeviceConfigObjectGetDisableStreamingIndicator(PyObject* self, PyObject* args)
{
	CHECK_ARGNUM(args, 0);

	if (m_cfg.disable_streaming_indicator)
		Py_RETURN_TRUE;
	Py_RETURN_FALSE;
}
