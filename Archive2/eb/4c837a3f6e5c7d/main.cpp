#include <type_traits>
#include <iostream>
#include <functional>

void func( int i )
{
    auto f = [&]() { std::cout << i << std::endl; };
    f();
}


int main()
{
    func( 5 );
}