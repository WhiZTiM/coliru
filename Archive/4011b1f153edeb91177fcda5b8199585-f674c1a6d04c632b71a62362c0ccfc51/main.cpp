#include <iostream>

struct C {
    C() {throw 0;}
};

struct A : C {
    A() {
        try {
            std::cout << "normal" << std::endl;
        } catch(...) {
            std::cout << "exception" << std::endl;
        }
    }
};

int main()
{
    A a;
    return 0;
}