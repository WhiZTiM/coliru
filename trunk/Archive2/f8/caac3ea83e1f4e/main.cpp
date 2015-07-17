#include <iostream>
#include <type_traits>

class X {};
class A : public X {};
class B {};

// On veut predefinir foo si T descend de la classe X

template<class T, typename = void>
class Base
{
public:
    virtual void foo() = 0;
};

template<class T>
struct Base<T, typename std::enable_if<std::is_base_of<X, T>::value>::type>
{
    virtual void foo() {}
};

int main()
{
    Base<A> a;
    //Base<B> b; // ok, error
    
    return 0;
}
