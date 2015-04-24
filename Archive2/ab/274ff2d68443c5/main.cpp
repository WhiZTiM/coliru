#include <iostream>

struct Base0 {
    int b0;
};

struct Base1 {
    int b1;
};

struct Derived : Base0, Base1 {};

int main() {
    Derived *p = nullptr;
    Base0 *p0 = p;
    Base1 *p1 = p;
    
    std::cout
        << "Derived : " << (void*)p
        << "\nBase0 : " << (void*)p0
        << "\nBase1 : " << (void*)p1 << '\n';
}