#include <iostream>

void func(int* i)
{
    *i = 44;
}

void func2()
{
    int myVal; // gcc will print warning: 'myVar' may be used uninitialized in this function
    func(&myVal);
    std::cout << myVal;
}

int main()
{
    func2();
}