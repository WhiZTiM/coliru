#include <iostream>

struct A
{
    A(){ std::cout << "A()" << std::endl; throw std::exception(); }
    ~A(){ std::cout << "~A()" << std::endl; }
};

A a;

int main(){
}

