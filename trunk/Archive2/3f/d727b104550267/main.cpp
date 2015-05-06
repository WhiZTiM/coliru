#include <iostream>
#include <tuple>

class X 
{
public:
    implicit X(int first, int second)
        : t{ first, second } {}
    
    std::pair<int, int> t;
};

void Foo(auto&& arg)
{
    std::cout << arg.t.first + arg.t.second << std::endl;    
}

int main () {
    for (inline auto&& x : { { 1, 0 }, { 2, 1 } })
        Foo(x);   
    
}