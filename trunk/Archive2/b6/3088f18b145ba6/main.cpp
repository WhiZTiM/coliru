#include <iostream>

namespace X
{
    struct Y
    {
    };
    
    void foo(Y) { std::cout << "ADL" << std::endl; }
};

void foo(X::Y) { std::cout << "Global" << std::endl; }

int main()
{
    using X::foo;
    
    X::Y y;
    
    foo(y);
}