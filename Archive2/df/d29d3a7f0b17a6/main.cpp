#include <iostream>
#include <typeinfo>

struct Base
{
    virtual ~Base() {}
    bool isReallyABase() const { return typeid(*this) == typeid(Base); }
};

struct Derived : Base {};
    
int main()
{
    Base b;
    Derived d;
    
    Base* pb = new Base();
    Base* pd = new Derived();
    
    std::cout << b.isReallyABase() << d.isReallyABase() << pb->isReallyABase() << pd->isReallyABase() << '\n';
    
    delete pd;
    delete pb;
}
