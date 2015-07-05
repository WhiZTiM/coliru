#include <iostream>

template <class T>
struct B
{
    B(int) { std::cout << "B ctor\n"; }
};

template <template <class> class C, class T>
struct D : C<T>
{
    using C<T>::C;
};


int main() {

    D<B,int> d(42);

    return 0;
}
