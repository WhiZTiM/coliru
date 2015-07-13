#include <iostream>
#include <string>

#include <memory>
#include <cmath>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

struct A {
    A()
    {
        std::cout << "constructor" << std::endl;
    }
    
    A(const A& from)
    {
        std::cout << "copy" << std::endl;
    }
    
    A(A&& from)
    {
        std::cout << "move" << std::endl;
    }
    
    ~A()
    {
        std::cout << "destroy" << std::endl;
    }
};

struct B {
    A a1;
    A a2;
};

int main()
{
    {
        B b{A(), A()};
    }
    
    std::cout << "---" << std::endl;
    
    std::vector<A> v = { A() };
    return 0;
}
