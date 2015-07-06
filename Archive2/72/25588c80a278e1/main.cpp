#include <iostream>

int main()
{
    int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
    const int n = sizeof(array) / sizeof( array[0] ) ;

    // normal order
    for( int i = 0 ; i < n ; ++i ) std::cout << array[i] ;
    std::cout << '\n' ;

    // reverse order
    for( int i = 0 ; i < n ; ++i ) std::cout << array[ (n-1) - i ] ;
    std::cout << '\n' ;
}
