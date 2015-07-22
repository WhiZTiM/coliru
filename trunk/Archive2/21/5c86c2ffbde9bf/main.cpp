#include <iostream>
#include <boost/python.hpp>

class ORM
{
public:
  void foo()
  {
    std::cout << "foo" << std::endl;
  }
};

BOOST_PYTHON_MODULE(orm)
{
  namespace python = boost::python;
  python::class_<ORM>("ORM")
      .def("foo", &ORM::foo)
    ;
}