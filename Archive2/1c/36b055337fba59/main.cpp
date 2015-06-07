// virtual members
#include <iostream>
using namespace std;

struct A
{
    virtual void func()
    {
        std::cout << "A" << std::endl;
    }
};

struct B : public A
{
};

struct C : public B
{
    void func()
    {
        std::cout << "C" << std::endl;
    }
};

int main ()
{
    C v;
    A* ptr = &v;
    
    ptr->func();
    return 0;
}
