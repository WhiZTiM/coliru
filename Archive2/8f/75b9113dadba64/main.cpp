#include <iostream>
#include <functional>
#include <vector>

struct A {
    void aFoo() { std::cout << "From A\n"; }
};

struct B {
    void bFoo() { std::cout << "From B\n"; }
};

struct C {
    void c1Foo() { std::cout << "From C1\n"; }
    void c2Foo() { std::cout << "From C2\n"; }
};

int main() {
    A a; B b; C c;
    std::vector<std::function<void()>> vector {
        std::bind(&A::aFoo, a),
        std::bind(&B::bFoo, b),
        std::bind(&C::c1Foo, c),
        std::bind(&C::c2Foo, c)
    };
    for (auto fn : vector)
        fn();
}