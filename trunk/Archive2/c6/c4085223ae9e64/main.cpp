#include <iostream>

template < typename T >
decltype( auto ) f( T param )
{
    return param + 1;
}

int main()
{
    auto i = f( 10 );
    std::cout << i;
    return 0;
}