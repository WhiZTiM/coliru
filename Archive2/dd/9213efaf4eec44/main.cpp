#include <iostream>

template<typename _Int>
class Base
{
    // ...
    virtual _Int Foo() = 0;
};

template<typename T>
class Derived
    : public Base<Derived<T>>
{
public:
    // ...
    Derived<T> Foo() override
    {
        return (*this);
    }
};

int main() {
    Derived<int> x;
    x.Foo();
}