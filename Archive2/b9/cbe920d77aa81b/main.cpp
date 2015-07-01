#include <iostream>

struct B {
    virtual void f() = 0;
    virtual void g() = 0;
};

template <class T>
struct M1 : B { };

template <class T>
struct M2 : M1<T> { 
    virtual void g() override
    {
        f();
    }
};

struct D : M2<int> {
    virtual void f() override { std::cout << "D::f\n"; }
};

int main() {
    D d;  
    d.g();

	return 0;
}
