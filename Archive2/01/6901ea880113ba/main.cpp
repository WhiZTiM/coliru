#include <iostream>    

void foo(void(&f)(int))
{
    std::cout << "YOU LOSE" << std::endl;
}

void foo(void(&&f)(int))
{
     std::cout << "YOU WIN" << std::endl;
}

void f(int) {}

struct wrap {
    using T = void(&&)(int);
    operator T() { return f; }
};

int main()
{
    foo(wrap());
}