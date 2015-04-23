#include <iostream>

class A{};
class B : public A{};

B* func() {return nullptr;} 

int main()
{
    A* a = nullptr;
    a = func();
    std::cout << a;
}