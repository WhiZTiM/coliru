#include <iostream>

struct Foo
{
    template<typename ... Args>
    void bar();
    
    template<typename T1>
    void bar();
};

template<typename ... Args>
void Foo::bar()
{
    std::cout << "Called unspecialized" << std::endl;
}

template<typename T1>
void Foo::bar()
{
    std::cout << "Called single argument type specialized" << std::endl;
}

struct A {};

int main()
{
    std::cout << "Hello World" << std::endl;
    
    Foo().bar<A>();
    return 0;
}