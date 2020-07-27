#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <PyKinect/device.h>
#include <PyKinect/capture.h>

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

	pModule = PyModule_Create(&PyKinectModule);
	if (!pModule)
		return NULL;

	Py_INCREF(&DeviceObjectType);
	if (PyModule_AddObject(pModule, "Device", (PyObject*)&DeviceObjectType) < 0)
	{
		Py_DECREF(&DeviceObjectType);
		Py_DECREF(&pModule);
		return NULL;
	}

	Py_INCREF(&CaptureObjectType);
	if (PyModule_AddObject(pModule, "Capture", (PyObject*)&CaptureObjectType) < 0)
	{
		Py_DECREF(&CaptureObjectType);
		Py_DECREF(&pModule);
		return NULL;
	}

	return pModule;
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


void printSerial(k4a_device_t device)
{
	// Get the size of the serial number
	size_t serial_size = 0;
	k4a_device_get_serialnum(device, NULL, &serial_size);

	// Allocate memory for the serial, then acquire it
	char* serial = (char*)malloc(serial_size);
	k4a_device_get_serialnum(device, serial, &serial_size);
	printf("Opened device: %s\n", serial);
	free(serial);
}
