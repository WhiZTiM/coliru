#include <type_traits>
#include <iostream>

template<typename T, std::enable_if< std::is_enum<T>::value  >::type = 0>
inline bool func(T & t, int x)
{
    std::cout << "enum" << std::endl;
}
/*
template<>
inline bool func<char>(char & t, int x)
{
    std::cout << "char" << std::endl;
}
*/
template<typename T, std::enable_if< !std::is_enum<T>::value >::type = 0>
inline bool func(T & t, int x)
{
    std::cout << "general" << std::endl;
}


enum FooEnum
{
    Foo,
    Bar,
};

int main()
{
    FooEnum foo(Foo);
    func(foo, 1);
    
    char c(15);
    func( c, 1);
    
    int i(15);
    func( i, 1);
    
    float f(15);
    func( f, 1);
    
}