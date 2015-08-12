#include <iostream>

struct Foo
{
    template <typename X, typename T, typename V, typename ... Args>
    static void f( );
    
    template <typename X, typename T>
    static void f( );
    
    template<typename X>
    static void f( );
};

template <typename X, typename T>
void Foo::f( )
{
    std::cout << "Swallowed last two arguments." << std::endl;
}

template <typename X, typename T, typename V, typename ... Args>
void Foo::f( )
{
    std::cout << "Processing last three arguments." << std::endl;
    Foo::f <X, V, Args...>( );
}

template <typename X> void Foo::f( )
{
    std::cout << "Swallowed the last argument." << std::endl;
}

int main()
{
    Foo foo;
    foo.f<int>();
    foo.f<int, int>();
    foo.f<int, int, int>();
}
