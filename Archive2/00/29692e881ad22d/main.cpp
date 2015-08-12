#include <iostream>
#include <type_traits>

struct Foo
{
    template <typename X, typename T, typename ... Args>
    static auto f( )
        -> typename std::enable_if<(sizeof...(Args) > 0)>::type;
    
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

template <typename X, typename T, typename ... Args>
auto Foo::f( )
    -> typename std::enable_if<(sizeof...(Args) > 0)>::type
{
    std::cout << "Processing last three arguments." << std::endl;
    Foo::f<X, Args...>( );
}

template <typename X>
void Foo::f( )
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
