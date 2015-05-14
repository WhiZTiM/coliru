#include <iostream>
#include <string>
#include <vector>

class A
{
public:
    virtual void Foo(int foos[]);
    virtual void Foo(int foo);
};

class B : public A
{
public:
    void Foo(int foo) override;
};

int main()
{
    B* b = new B();
    
    int ints[] = {0, 1, 2, 3};
    b->Foo(ints);
}
