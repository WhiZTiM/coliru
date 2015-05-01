#include <iostream>

struct A{ virtual ~A(){ } };

struct B : A { };

A *a = new B;

    
int main()
{
    delete a; //UB?
}