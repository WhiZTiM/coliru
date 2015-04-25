#include <iostream>

using std::cout;
using std::endl;

struct A
{
    virtual void foo(){ };
    
    A(int i)
    {
        cout << "A(" << i << ")" << endl;
    }
};

struct B : virtual A
{
    virtual void bar() = 0;
    
    B() : A(5)
    {
        cout << "B()" << endl;
    }
};

struct C : B
{
    void bar(){ };
    C() : A(20), B()
    {
        cout << "C()" << endl;
    }
};

C c;

int main()
{
    
}