
#include <iostream>

class Base
{
    public:
    virtual void func()
    {
        std::cout << "Base::func" << std::endl;
    }
};

class Derive : public Base
{
    public:
    virtual void func()
    {
        std::cout << "Derive::func" << std::endl;
    }
};

int main()
{
    Derive d;
    d.Base::func();
    return 0;
}