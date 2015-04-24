#include <boost/python.hpp>

struct base {};

void foo(boost::shared_ptr<base>) {}

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;
  python::class_<base, boost::shared_ptr<base>, boost::noncopyable>(
      "Base", python::init<>())
    ;
    
  python::def("foo", &foo);
}
