#include <iostream>
#include <typeinfo>

struct S {
    virtual ~S() {}  
};

S &f() {
    std::cout << "foo";
    static S s;
    return s;
}

int main() {
    typeid(f());   
}