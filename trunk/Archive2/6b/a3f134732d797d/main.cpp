#include <iostream>

void test()
{
    int y = 199;
    ++y;
    std::cout << y << std::endl;
}

void test2()
{
    int y;
    ++y;
    std::cout << y << std::endl;
}

int main()
{
    test2();
    test2();
    test();
    test2();
    test2();
}
