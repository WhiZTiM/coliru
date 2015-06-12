#include <iostream>

using namespace std;

struct A
{
    virtual void foo() { cout << "A::foo()" << endl; };
};

struct B : A
{
    void foo() { cout << "B::foo()" << endl; };
};

struct C : B
{
    void foo() { cout << "C::foo()" << endl; };
};

int main()
{
    C c;
    A& a = c;
    
    a.foo(); // Imprime C::foo()
}