#include <iostream>
#include <vector>
#include <type_traits>

class Bar {};

template<typename T, typename std::enable_if<!std::is_same<T, Bar>::value>::type* = nullptr>
auto foo(T&& t) { std::cout<<"general version"<<std::endl; }

template<typename T, typename std::enable_if<std::is_same<T, Bar>::value>::type* = nullptr>
auto foo(T&& t) { std::cout<<"Bar version"<<std::endl; }
    
int main()
{
    foo(25);
    foo(Bar());
}