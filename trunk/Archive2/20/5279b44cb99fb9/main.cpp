#include <iostream>
class Base {
public: 
    virtual void member_func() {
    std::cout << "Base" << '\n'; };
};

class Derived : public Base {
public:
    virtual void member_func() { std::cout << "Derived" << '\n'; };
};

int main() {
    typedef void (Base::*MFP)();
    MFP memfunc_ptr;
    memfunc_ptr = &Base::member_func;   // When I replace Base by Derived the code doesn't compile. Why?
    Derived d;
    (d.*memfunc_ptr)(); 
}