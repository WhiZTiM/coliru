#include <type_traits>
#include <iostream>
#include <functional>

std::function<void()> func( int i )
{
    return [&]() { std::cout << i << std::endl; };
}


int main()
{
    func( 5 )();
    func( 15 )();
}