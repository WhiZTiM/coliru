// virtual members
#include <iostream>
using namespace std;

class A
{
};

void test2(const A&)
{
    std::cout << "const A&" << std::endl;
}

void test2(A&&)
{
    std::cout << "A&&" << std::endl;
}

void test1(A&& a)
{
    test2(a);
}

int main ()
{
    test1(A());
    
    return 0;
}
