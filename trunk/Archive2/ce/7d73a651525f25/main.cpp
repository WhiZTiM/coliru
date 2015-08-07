#include <iostream>

struct Foo {
    int a = 2;  
};

int Foo::*getA() {return &Foo::a;}  

int main() {
    Foo foo;
    std::cout << foo.*getA();
}