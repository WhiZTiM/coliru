#include <iostream>

struct Base {};

template <size_t S>
class Foo : public Base
{
public:
    Foo(int* a)
        : val(*a)
        , rest(a + 1)
    {
    }
    
private:
    int val;
    Foo<S-1> rest;
};

template <>
class Foo<1> : public Base
{
public:
    Foo(int* a)
        : val(*a)
    {
    }
    
private:
    int val;
};


int main()
{
    std::cout << sizeof(Foo<3>) << std::endl;
}