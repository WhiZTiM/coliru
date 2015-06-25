#include <iostream>
#include <string>

struct A {
    A() = default;
    
    A(A&& obj) : i(obj.i) {
        std::cout << "move ctor" << std::endl;
    }
    
    A(const A& obj) : i(obj.i) {
        std::cout << "copy ctor" << std::endl;
    }
        
    int i = 0;
};

A create()
{
    return A();
}

int main()
{
    auto a = create();
    
    return 0;
}
