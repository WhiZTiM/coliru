#include <iostream>
#include <type_traits>

class X {};
class A : public X {};
class B {};

struct Abstract {
    virtual void foo() = 0;
};

template <class T>
struct Concrete : Abstract {
    virtual void foo() override {};
};

template <class T>
struct Base
: std::conditional_t<
    std::is_base_of<X,T>{},
    Concrete<T>,
    Abstract
> {};

int main()
{
    Base<A> a;
    Base<B> b; // ok, error
    
    return 0;
}
