#include<iostream>
#include<vector>
   
struct A
{
    int a;
    A(int) { }
    virtual int foo(){ std::cout << "base" << std::endl; return 5; }
};

struct B : A
{
    int b;
    B(): b(9), A(foo()) { }
    virtual int foo(){ std::cout << "derived" << std::endl; return 6; }
};

B b;

int main(){ }