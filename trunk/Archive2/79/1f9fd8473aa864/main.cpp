#include <iostream>
#include <vector>

int main()
{
    std::vector<int> seq { 12, 34, 67, 23, 82, 38, 77, 52, 26 } ;

    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;

    // option one: iterate in reverse
    int delta = -1 ; // ++delta == 0
    for( auto iter = seq.rbegin() ; iter != seq.rend() ; ++iter )
        *iter += ++delta ;
    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;

    // option two: iterate forward
    delta = seq.size() ; // --delta == seq.size() - 1
    for( int& v : seq ) v += --delta ;
    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
