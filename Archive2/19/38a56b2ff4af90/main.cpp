#include <iostream>

using namespace std;

class Base
{
public:
    virtual void foo() = 0;
};

class Derived : public Base
{
public:
    void foo()
    {
        cout << "foo" << endl;
    }
};

int main()
{
    Derived D;
    void *p = &D;
    static_cast<Base*>(p)->foo();
    return 0;
}