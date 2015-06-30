#include <iostream>

struct A
{
    virtual void foo() = 0;
    A(){ init(); }
    void init(){ foo(); }
};

struct B : A
{
    virtual void foo();
};

B a;

int main(){
    return 0;
}

