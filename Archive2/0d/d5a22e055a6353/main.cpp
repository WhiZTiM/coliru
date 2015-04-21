//test.cpp
#include <iostream>
#include <vector>
#include <type_traits>

struct check_has_method
{
    template<typename T, typename X=std::is_same<int(T::*)(float),decltype(&T::Method)>>
    static X test(int);
    
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_method : decltype(check_has_method::test<T>(0)) {};


class A
{
public:
    int method(float x) { std::cout << "A!" << std::endl; return 0; }
};

class B
{
public:
    int Method(float y, float z) { std::cout << "B!" << std::endl; return 0; }
};

class C
{
public:
    void Method(float y) { std::cout << "C!" << std::endl; }
};

class D
{
public:
    int Method(float y) { std::cout << "D!" << std::endl; return 0; }
};


int main()
{
    //std::cout << whatever() << std::endl;
    static_assert(has_method<A>::value, "A doesn't have method");
    static_assert(has_method<B>::value, "B doesn't have method");
    static_assert(has_method<C>::value, "C doesn't have method");
    static_assert(has_method<D>::value, "D doesn't have method");

    return 0;
}
