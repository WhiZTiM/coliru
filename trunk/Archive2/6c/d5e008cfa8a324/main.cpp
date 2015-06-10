#include <iostream>

struct A
{
   virtual ~A() = 0;
   virtual void foo() = 0;
};

void A::foo(){ }
A::~A(){ std::cout << "~A()" << std::endl; }

struct B : A
{
    ~B(){ std::cout << "~B()" << std::endl; }
};

A *a = new B;


int main()
{
    delete a;
}