#include <iostream>
class Base {
public: 
    void member_func() {
    std::cout << "Base" << '\n'; };
};

class Derived : public Base {
public:
    void member_func() { std::cout << "Derived" << '\n'; };
};

int main() {
    typedef void (Base::*MFP)();
    MFP memfunc_ptr;
    memfunc_ptr = &Base::member_func;
    Derived d;
    (d.*memfunc_ptr)(); 
}