#include <Python.h>

int run_mymodule(char *, char *, char *, PyObject *) {
    return 42;
}

static PyObject * wrap_run_mymodule(PyObject *, PyObject *args) {
    char *file1, *file2, *file3;
    PyObject *tmpp;
    if(!PyArg_ParseTuple(args, "sssO", &file1, &file2, &file3, &tmpp))
        return NULL;
    return Py_BuildValue("i", run_mymodule(file1, file2, file3, tmpp));
}

static PyMethodDef myModule_methods[] = {
    {"run_mymodule", (PyCFunction) wrap_run_mymodule, METH_VARARGS},
    {NULL, NULL}
};

extern "C" void initmymodule(void)
{
    (void) Py_InitModule("mymodule", myModule_methods);
}