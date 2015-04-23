#include <Python.h>
#include <boost/python.hpp>
#include <iostream>

struct Base { };
struct Derived : Base { };

void foo(boost::shared_ptr<Base> ) {
    std::cout << "yay\n";
}

BOOST_PYTHON_MODULE(Test)
{
    using namespace boost;
    using namespace boost::python;
    
    class_<Base, shared_ptr<Base>, noncopyable>("Base", init<>())
    ;
    
    class_<Derived, bases<Base>, shared_ptr<Derived>, noncopyable>("Derived", init<>())
    ;
    
    def("foo", foo);
}
