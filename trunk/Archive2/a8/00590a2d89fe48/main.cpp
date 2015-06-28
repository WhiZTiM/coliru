#include <iostream>

struct A
{
    const int a = 10;
    virtual void foo() = 0;
};

void A::foo(){ std::cout << "foo" << std::endl; }

int main(int argc, char ** argv){ }

