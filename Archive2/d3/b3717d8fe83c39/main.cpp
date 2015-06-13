#include <iostream>

using namespace std;

struct A
{
    virtual ~A() { cout << "A::~A()" << endl; }
    virtual void foo() { cout << "A::foo()" << endl; }
};

struct B : A
{
    ~B() { cout << "B::~B()" << endl; }
    void foo() { cout << "B::foo()" << endl; }
};

struct C : B {};

struct D : C {   ~D() { cout << "D::~D()" << endl; }    };

struct E : D
{
    ~E() { cout << "E::~E()" << endl; }
    void foo() { cout << "E::foo()" << endl; }
};

int main()
{
    A* pa = new E;
    pa->foo();
    delete pa;
    
    cout << endl;
    
    C* pc = new E;
    pc->foo();
    delete pc;
}

