
#include <iostream>

class A
{
    //char name[40] = { "error with gcc" } ; // Compiler error
    char otherName[40]  = {'g','c','c'};
public:
    const char *getName() { return otherName; }
};

int main()
{
    A a;

    std::cout << a.getName() << std::endl;
}
