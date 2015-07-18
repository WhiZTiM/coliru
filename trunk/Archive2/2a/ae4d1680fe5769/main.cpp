#include <iostream>
#include <type_traits>

class X {};
class A : public X {};
class B {};

//On veut definir foo si T descend de la classe X

template <class T>
struct Abstract
{
    virtual void foo() = 0;
};

template <class T>
struct Concrete : Abstract<T>
{
    virtual void foo() override {};
};

template <class T>
struct Base :
    std::conditional< std::is_base_of<X,T>::value,
        Concrete<T>,
        Abstract<T>
    >::type
{
    
public:
    void bar()
    {
        foo(); // ???
    }
};

int main()
{
    Base<A> a;
    //Base<B> b;
    
    return 0;
}
