#include <iostream>           // std::cout
#include <algorithm>
#include <vector>
#include <list>

 
class A
{
    public:
        A() = default;
        
        virtual void print() const { std::cout << "A" << std::endl; }
};
 
class B : public A
{
    public:
        B() = default;
        
        virtual void print() const override { std::cout << "B" << std::endl; }
};

void foo(const A& a)
{
    a.print();
}
 
int main()
{
    B b;
    foo(b);
}