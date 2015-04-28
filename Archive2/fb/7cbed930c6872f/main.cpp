#include <iostream>

namespace X
{
    struct Y
    {
    };
    
    //void foo(Y) { std::cout << "specific" << std::endl; }
};

namespace blub
{
    template<class T>
    void foo(T) { std::cout << "general" << std::endl; }
}

int main()
{
    using blub::foo;
    
    X::Y y;
    
    foo(y);
}