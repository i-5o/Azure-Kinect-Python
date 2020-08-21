#ifndef PYKINECT_UTIL_H
#define PYKINECT_UTIL_H

#define PY_SSIZE_T_CLEAN

#define CHECK_ARGNUM(args, n)                                         \
	Py_ssize_t argNum = PyTuple_Size(args);                           \
	if (argNum != 1)                                                  \
	{                                                                 \
		char buf[64];                                                 \
		sprintf(buf, "Expected "#n" argument(s), got %llu", argNum);  \
		PyErr_SetString(PyExc_ValueError, buf);                       \
		return NULL;                                                  \
	}

#endif
