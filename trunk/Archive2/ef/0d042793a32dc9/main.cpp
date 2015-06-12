#include <type_traits>
#include <iostream>
#include <functional>

void func( int i )
{
    auto а = [&]() { std::cout << i << std::endl; };
    a();
}


int main()
{
    func( 5 );
}