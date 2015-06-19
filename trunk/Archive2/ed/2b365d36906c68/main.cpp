#include <iostream>

template<class T>
struct A {
    typedef T a;
};
template<class T>
struct B {
    typedef typename A<T>::a a;
    static a foo(a b);
};
template<class T>
a B<T>::foo(a b) {return b}

int main()
{
    std::cout << B<int>::foo(1);
}
