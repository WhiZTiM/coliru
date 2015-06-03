#include <iostream>

class Base
{
    virtual void delegate(int x) = 0;
public:
    Base& operator<<( int x) // we define this only in Base
    {
        delegate(x); // delegate, this must be overridden in all derived classes
        return *this;
    }
};

void Base::delegate(int x) // we can even define this
{
    std::cout << "Base::delegate x = " << x << std::endl;
}

class A : public Base
{
    void delegate(int x) override
    {
        std::cout << "A::delegate x = " << x << std::endl;
    }
};

class B : public Base
{
    void delegate(int x) override
    {
        std::cout << "B::delegate x = " << x << std::endl;
    }
};

int main()
{
    Base* pBase = new B;
    *pBase << 42;
}