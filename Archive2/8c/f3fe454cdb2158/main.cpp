#include <iostream>

template<class A, class B, class C>
A doFoo(const B &val)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return {};
}

struct ParticularC {};

template<class A, class B>
auto &myDoFoo = doFoo<A, B, ParticularC>;

int main() {
    myDoFoo<float, double>(42);
}