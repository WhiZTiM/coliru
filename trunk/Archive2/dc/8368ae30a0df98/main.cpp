#include <iostream>
#include <vector>

template < typename SEQ_CONTAINER > SEQ_CONTAINER construct_from_stdin()
{
    SEQ_CONTAINER result ;

    typename SEQ_CONTAINER::value_type value ; // the type of values held by the container

    while( std::cin >> value ) result.push_back(value) ;

    return result ;
}

int main()
{
    const auto seq = construct_from_stdin< std::vector<int> >() ;

    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
