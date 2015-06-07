#include <iostream>
#include <utility>

class A
{
};

void test3(const A&)
{
    std::cout << "const A&" << std::endl;
}

void test3(A&&)
{
    std::cout << "A&&" << std::endl;
}

void test1(A&& a)
{
    test3(a);
}

void test2(A&& a)
{
    test3(std::move(a));
}

int main ()
{
    test1(A());
    test2(A());
    
    return 0;
}
