#include <Python.h>
#include <iostream>
#include <boost/python.hpp>

using namespace boost;
using namespace boost::python;

struct Base { };

void foo(boost::shared_ptr<Base> )
{
    std::cout << "yay\n";
}

BOOST_PYTHON_MODULE(Test)
{
    class_<Base, shared_ptr<Base>, noncopyable>("Base", init<>());
    
    def("foo", foo);
}
