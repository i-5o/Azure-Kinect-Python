#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <PyKinect/device.h>

/*
 *
 * Python Module
 *
 */

static struct PyModuleDef PyKinectModule =
{
	PyModuleDef_HEAD_INIT,
	"PyKinect",             // Module name
	NULL,                   // Module documentation - provided in python wrapper
	-1,                     // Module keeps state in global variables
};

PyMODINIT_FUNC PyInit_PyKinect(void)
{
	PyObject* pModule;
	if (PyType_Ready(&DeviceObjectType) < 0)
		return NULL;

	pModule = PyModule_Create(&PyKinectModule);
	if (!pModule)
		return NULL;

	Py_INCREF(&DeviceObjectType);
	if (PyModule_AddObject(pModule, "device", (PyObject*)&DeviceObjectType) < 0)
	{
		Py_DECREF(&DeviceObjectType);
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

	if (PyImport_AppendInittab("PyKinect", PyInit_PyKinect) == -1)
	{
		fprintf(stderr, "Error:  could not extend in-built modules table\n");
		exit(1);
	}

	Py_SetProgramName(program);
	Py_Initialize();

	PyObject* pModule = PyImport_ImportModule("PyKinect");
	if (!pModule)
	{
		PyErr_Print();
		fprintf(stderr, "Error: could not import module 'PyKinect'\n");
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
