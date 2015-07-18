#include <iostream>
#include <vector>
#include <algorithm>

template < typename T > std::vector<T> reverse_vector( std::vector<T> seq )
{
    auto iter1 = seq.begin() ; // here auto is the type decltype( seq.begin() )
    auto iter2 = seq.rbegin() ; // and the compiler deduces the type

    while( iter1 < iter2.base() )
    {
        using std::swap ;
        swap( *iter1, *iter2 ) ;
        ++iter1 ;
        ++iter2 ;
    }

    return seq ;
}

int main()
{
    const std::vector<std::string> vec { "zero", "one", "two", "three", "four" } ;
    
    for( const auto& str : reverse_vector(vec) ) std::cout << str << ' ' ;
    std::cout << '\n' ;
}
