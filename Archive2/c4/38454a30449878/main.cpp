#include <iostream>

struct A{ virtual void foo(){ } };

struct B : A { virtual void foo(){ } };

A *a = new B;

    
int main()
{
    delete a; //Is it en
}