#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

struct X
{
    X(int x) : x{x} { }
    
    void foo() { std::cout << x; }
    
    int x;
};

int main()
{
    auto f = std::bind(&X::foo, std::placeholders::_1);
    
    X x{42};
    f(x);
    
}