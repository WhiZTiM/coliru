//test.cpp
#include <iostream>
#include <vector>
#include <type_traits>

class Base
{
public:
    int Method(int x) { std::cout << "Base!" << std::endl; return 0; }
};

class Derived : public Base
{
public:
    int Method(float y) { std::cout << "Derived!" << std::endl; return 0; }
};

template<typename T>
void HasMethodSig()
{
    static_assert(std::is_same<int(T::*)(float),decltype(&T::Method)>::value,"Function signatures don't match");
}

int main()
{
    HasMethodSig<Derived>();

    return 0;
}
