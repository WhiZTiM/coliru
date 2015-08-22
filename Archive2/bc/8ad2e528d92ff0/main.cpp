#include <iostream>

struct A { virtual ~A() {} };
struct B : A {};
struct C : A {};

struct D : B, C {};

int main() {
    D *d = new D;
    
    // A *a = d; // error, ambiguous

    A *a1 = static_cast<B*>(d);
    A *a2 = static_cast<C*>(d);

    std::cout << "d: " << d << '\n';
    
    std::cout << "a1: " << a1 << '\n';
    std::cout << "a2: " << a2 << '\n';

    std::cout << "a1 -> D: " << dynamic_cast<D*>(a1) << '\n';
    std::cout << "a2 -> D: " << dynamic_cast<D*>(a2) << '\n';
}
