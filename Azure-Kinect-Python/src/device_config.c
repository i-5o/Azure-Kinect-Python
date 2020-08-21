#include <PyKinect/device_config.h>
#include <PyKinect/util.h>

#define pSelf     ((DeviceConfigObject*)self)
#define m_cfg     pSelf->config

 /*
  *
  * DeviceConfigObject Standard Functions
  *
  */

PyObject* DeviceConfigObjectNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
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

int DeviceConfigObjectInit(PyObject* self, PyObject* args, PyObject* kwds)
{
	m_cfg = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;

	return 0;
}

void DeviceConfigObjectDealloc(PyObject* self)
{
	PyTypeObject* tp = Py_TYPE(self);
	tp->tp_free(self);
	Py_DECREF(tp);
}

PyObject* DeviceConfigObjectRepr(PyObject* self)
{
	char cfmtbuf[32];
	char cresbuf[32];
	char dpmdbuf[32];
	char cfpsbuf[64];
	char simgbuf[6 ];
	char ddlybuf[11];
	char wsmdbuf[64];
	char sdombuf[11];
	char sindbuf[6 ];

	// image_format
	switch (m_cfg.color_format)
	{
	case K4A_IMAGE_FORMAT_COLOR_MJPG:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_COLOR_MJPG");
		break;
	case K4A_IMAGE_FORMAT_COLOR_NV12:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_COLOR_NV12");
		break;
	case K4A_IMAGE_FORMAT_COLOR_YUY2:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_COLOR_YUY2");
		break;
	case K4A_IMAGE_FORMAT_COLOR_BGRA32:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_COLOR_BGRA32");
		break;
	case K4A_IMAGE_FORMAT_DEPTH16:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_DEPTH16");
		break;
	case K4A_IMAGE_FORMAT_IR16:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_IR16");
		break;
	case K4A_IMAGE_FORMAT_CUSTOM8:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_CUSTOM8");
		break;
	case K4A_IMAGE_FORMAT_CUSTOM16:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_CUSTOM16");
		break;
	case K4A_IMAGE_FORMAT_CUSTOM:
		strcpy(cfmtbuf, "K4A_IMAGE_FORMAT_CUSTOM");
		break;
	default:
		strcpy(cfmtbuf, "Invalid");
	}

	// color_resolution
	switch (m_cfg.color_resolution)
	{
	case K4A_COLOR_RESOLUTION_OFF:
		strcpy(cresbuf, "K4A_COLOR_RESOLUTION_OFF");
		break;
	case K4A_COLOR_RESOLUTION_720P:
		strcpy(cresbuf, "K4A_COLOR_RESOLUTION_720P");
		break;
	case K4A_COLOR_RESOLUTION_1080P:
		strcpy(cresbuf, "K4A_COLOR_RESOLUTION_1080P");
		break;
	case K4A_COLOR_RESOLUTION_1440P:
		strcpy(cresbuf, "K4A_COLOR_RESOLUTION_1440P");
		break;
	case K4A_COLOR_RESOLUTION_1536P:
		strcpy(cresbuf, "K4A_COLOR_RESOLUTION_1536P");
		break;
	case K4A_COLOR_RESOLUTION_2160P:
		strcpy(cresbuf, "K4A_COLOR_RESOLUTION_2160P");
		break;
	case K4A_COLOR_RESOLUTION_3072P:
		strcpy(cresbuf, "K4A_COLOR_RESOLUTION_3072P");
		break;
	default:
		strcpy(cresbuf, "Invalid");
	}

	// depth_mode
	switch (m_cfg.depth_mode)
	{
	case K4A_DEPTH_MODE_OFF:
		strcpy(dpmdbuf, "K4A_DEPTH_MODE_OFF");
		break;
	case K4A_DEPTH_MODE_NFOV_2X2BINNED:
		strcpy(dpmdbuf, "K4A_DEPTH_MODE_NFOV_2X2BINNED");
		break;
	case K4A_DEPTH_MODE_NFOV_UNBINNED:
		strcpy(dpmdbuf, "K4A_DEPTH_MODE_NFOV_UNBINNED");
		break;
	case K4A_DEPTH_MODE_WFOV_2X2BINNED:
		strcpy(dpmdbuf, "K4A_DEPTH_MODE_WFOV_2X2BINNED");
		break;
	case K4A_DEPTH_MODE_WFOV_UNBINNED:
		strcpy(dpmdbuf, "K4A_DEPTH_MODE_WFOV_UNBINNED");
		break;
	case K4A_DEPTH_MODE_PASSIVE_IR:
		strcpy(dpmdbuf, "K4A_DEPTH_MODE_PASSIVE_IR");
		break;
	default:
		strcpy(dpmdbuf, "Invalid");
	}

	// camera_fps
	switch (m_cfg.camera_fps)
	{
	case K4A_FRAMES_PER_SECOND_5:
		strcpy(cfpsbuf, "K4A_FRAMES_PER_SECOND_5");
		break;
	case K4A_FRAMES_PER_SECOND_15:
		strcpy(cfpsbuf, "K4A_FRAMES_PER_SECOND_15");
		break;
	case K4A_FRAMES_PER_SECOND_30:
		strcpy(cfpsbuf, "K4A_FRAMES_PER_SECOND_30");
		break;
	default:
		strcpy(cfpsbuf, "Invalid");
	}

	// synchronized_images_only
	if (m_cfg.synchronized_images_only)
		strcpy(simgbuf, "true");
	else
		strcpy(simgbuf, "false");

	// depth_delay_off_color_usec
	itoa(m_cfg.depth_delay_off_color_usec, ddlybuf, 10);

	// wired_sync_mode
	switch (m_cfg.wired_sync_mode)
	{
	case K4A_WIRED_SYNC_MODE_STANDALONE:
		strcpy(wsmdbuf, "K4A_WIRED_SYNC_MODE_STANDALONE");
		break;
	case K4A_WIRED_SYNC_MODE_MASTER:
		strcpy(wsmdbuf, "K4A_WIRED_SYNC_MODE_MASTER");
		break;
	case K4A_WIRED_SYNC_MODE_SUBORDINATE:
		strcpy(wsmdbuf, "K4A_WIRED_SYNC_MODE_SUBORDINATE");
		break;
	default:
		strcpy(wsmdbuf, "Invalid");
	}

	// subordinate_delay_off_master_usec
	itoa(m_cfg.subordinate_delay_off_master_usec, sdombuf, 10);

	//disable_streaming_indicator
	if (m_cfg.disable_streaming_indicator)
		strcpy(sindbuf, "true");
	else
		strcpy(sindbuf, "false");

	return PyUnicode_FromFormat(
		"Device Configuration:\n"
		"\timage_format:                      %s\n"
		"\tcolor_resolution:                  %s\n"
		"\tdepth_mode:                        %s\n"
		"\tcamera_fps:                        %s\n"
		"\tsynchronized_images_only:          %s\n"
		"\tdepth_delay_off_color_usec:        %s\n"
		"\twired_sync_mode:                   %s\n"
		"\tsubordinate_delay_off_master_usec: %s\n"
		"\tdisable_streaming_indicator:       %s\n"
		,cfmtbuf
		,cresbuf
		,dpmdbuf
		,cfpsbuf
		,simgbuf
		,ddlybuf
		,wsmdbuf
		,sdombuf
		,sindbuf
	);
}

/*
 *
 * DeviceConfigObject Member Functions
 *
 */

PyObject* DeviceConfigObjectSetImageFormat(PyObject* self, PyObject* args)
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

PyObject* DeviceConfigObjectGetImageFormat(PyObject* self, PyObject* args)
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
