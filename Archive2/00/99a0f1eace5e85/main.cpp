#include<iostream>
#include<vector>
   
struct A
{
    A(){ foo(); }
    virtual void foo(){ std::cout << "base" << std::endl; }
};

struct B : A
{
    virtual void foo(){ std::cout << "derived" << std::endl; }
};

B b;

int main(){ }