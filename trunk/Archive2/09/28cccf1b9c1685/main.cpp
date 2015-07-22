#include <vector>
#include <boost/python.hpp>

// Mocks...
enum { NPY_FLOAT };
typedef int npy_intp;
PyObject* PyArray_SimpleNewFromData(int, npy_intp*, int, void*)
{
  return PyString_FromString("hello world");
}

boost::python::object build_day(int year, int day)
{
  const int HEIGHT = 5;
  const int WIDTH = 5;

  std::vector<std::vector<float> > array(
      WIDTH, std::vector<float>(HEIGHT));

  npy_intp dims[2] = {WIDTH, HEIGHT};
  
  namespace python = boost::python;
  PyObject* arr = PyArray_SimpleNewFromData(2, dims, NPY_FLOAT, &array);
  python::handle<> handle(arr);
  return python::object(handle);
}

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;
  python::def("build_day", &build_day, python::args("year", "day"));
}