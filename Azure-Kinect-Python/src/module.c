#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <PyKinect/device.h>
#include <PyKinect/capture.h>
#include <PyKinect/image.h>
#include <PyKinect/device_config.h>

/*
 *
 * Python Module
 *
 */

static struct PyModuleDef PyKinectModule =
{
	PyModuleDef_HEAD_INIT,
	"_PyKinect",            // Module name
	NULL,                   // Module documentation - provided in python wrapper
	-1,                     // Module keeps state in global variables
};

PyMODINIT_FUNC PyInit__PyKinect(void)
{
	PyObject* pModule;
	if (PyType_Ready(&DeviceObjectType) < 0)
		return NULL;
	if (PyType_Ready(&CaptureObjectType) < 0)
		return NULL;
	if (PyType_Ready(&ImageObjectType) < 0)
		return NULL;

	pModule = PyModule_Create(&PyKinectModule);
	if (!pModule)
		return NULL;

	Py_INCREF(&DeviceObjectType);
	if (PyModule_AddObject(pModule, "Device", (PyObject*)&DeviceObjectType) < 0)
		goto DeviceObjectError;

	Py_INCREF(&CaptureObjectType);
	if (PyModule_AddObject(pModule, "Capture", (PyObject*)&CaptureObjectType) < 0)
		goto CaptureObjectError;

	Py_INCREF(&ImageObjectType);
	if (PyModule_AddObject(pModule, "Image", (PyObject*)&ImageObjectType) < 0)
		goto ImageObjectError;

	Py_INCREF(&DeviceConfigObjectType);
	if (PyModule_AddObject(pModule, "DeviceConfig", (PyObject*)&DeviceConfigObjectType) < 0)
		goto DeviceConfigObjectTypeError;

	return pModule;

DeviceConfigObjectTypeError:
	Py_DECREF(&DeviceConfigObjectType);

ImageObjectError:
	Py_DECREF(&ImageObjectType);

CaptureObjectError:
	Py_DECREF(&CaptureObjectType);

DeviceObjectError:
	Py_DECREF(&DeviceObjectType);

	Py_DECREF(&pModule);
	return NULL;
}

int main(int argc, char* argv[])
{
	wchar_t* program = Py_DecodeLocale(argv[0], NULL);
	if (!program)
	{
		fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
		exit(1);
	}

	if (PyImport_AppendInittab("_PyKinect", PyInit__PyKinect) == -1)
	{
		fprintf(stderr, "Error:  could not extend in-built modules table\n");
		exit(1);
	}

	Py_SetProgramName(program);
	Py_Initialize();

	PyObject* pModule = PyImport_ImportModule("_PyKinect");
	if (!pModule)
	{
		PyErr_Print();
		fprintf(stderr, "Error: could not import module '_PyKinect'\n");
	}

	PyMem_RawFree(program);
	return 0;
}
