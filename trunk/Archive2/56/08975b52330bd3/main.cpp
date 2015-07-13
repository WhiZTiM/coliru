#include <iostream>
#include <typeinfo>

template <class T>
struct Tem
{
    typedef T NestedType;
    void print() const { std::cout << typeid(T).name() << '\n'; }
};


template <class Bound, class U>
struct rebinder;

template <template <class> class Binder, class B, class U>
struct rebinder<Binder<B>, U>
{
    typedef Binder<U> type; 
};


int main()
{
    Tem<int> i;
    i.print();
    rebinder<Tem<int>, float>::type f;
    f.print();
}
