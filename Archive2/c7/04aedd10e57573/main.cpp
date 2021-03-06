#include <iostream>
#include <string>

// return the position of the largest element. invariant: n > 0
std::size_t pos_largest( const std::string array[], std::size_t n )
{
    std::size_t pos_largest = 0 ;
    for( std::size_t i = 1 ; i < n ; ++i )
        if( array[pos_largest] < array[i] ) pos_largest = i ;
    return pos_largest ;
}

void do_swap( std::string& a, std::string& b ) // simple swap, not using move
{
    std::string temp = a ;
    a = b ;
    b = temp ;
}

// for both arrays, bring the element at position 'pos' to the front
void bring_to_front( std::string a[], std::string b[], std::size_t pos )
{
    do_swap( a[0], a[pos] ) ;
    do_swap( b[0], b[pos] ) ;
}

// sort descending on primary, keeping secondary aligned with primary
void parallel_sort_descending( std::string primary[], std::string secondary[], std::size_t n )
{
    if( n > 1 )
    {
        // get the largest value to the front of both sequences
        bring_to_front( primary, secondary, pos_largest( primary, n ) ) ;

        // repeat for the tail of (the remaining elements in) the sequences
        parallel_sort_descending( primary+1, secondary+1, n-1 ) ;
    }
}

int main()
{
    const std::size_t n = 5 ;
    std::string a[n] = { "2",   "0",    "4",    "1",   "3" } ;
    std::string b[n] = { "two", "zero", "four", "one", "three" } ;

    parallel_sort_descending( a, b, n ) ; // sort on a, keeping b aligned with a
    for( std::size_t i = 0 ; i < n ; ++i ) std::cout << a[i] << ' ' << b[i] << '\n' ;
    std::cout << "--------------\n" ;

    parallel_sort_descending( b, a, n ) ; // sort on b, keeping a aligned with b
    for( std::size_t i = 0 ; i < n ; ++i ) std::cout << b[i] << ' ' << a[i] << '\n' ;
}
