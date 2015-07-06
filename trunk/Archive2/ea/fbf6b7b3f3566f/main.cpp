#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>

// insert a number maintaining sorted order
template < typename A, template<typename,typename> class CNTR >
void insert( CNTR<int,A>& sorted_seq, int v ) // invariant: sorted
{ sorted_seq.insert( std::upper_bound( std::begin(sorted_seq), std::end(sorted_seq), v ), v ) ; }

// erase the number at the middle of the sequence, maintaining original order
template < typename A, template<typename,typename> class CNTR >
void erase( CNTR<int,A>& seq ) // invariant: !empty()
{ seq.erase( std::next( std::begin(seq), seq.size()/2 ) ) ; }

template < typename A, template<typename,typename> class CNTR >
auto test_it( CNTR<int,A>& seq, const std::vector<int>& values )
{
    const auto start = std::clock() ;
    for( int v : values ) insert( seq, v ) ; // insert values in sorted order
    while( seq.size() > values.size()/2 ) erase(seq) ; // remove values in the middle
    return ( std::clock() - start ) * 1000.0 / CLOCKS_PER_SEC ;
}

int main()
{
    constexpr std::size_t N = 20'000 ;
    std::vector<int> values(N) ;
    std::iota( std::begin(values), std::end(values), 0 ) ;
    std::shuffle( std::begin(values), std::end(values), std::mt19937( std::random_device{}() ) ) ;

    std::cout << "vector: " ;
    std::vector<int> vec ;
    std::cout << test_it( vec, values ) << " millisecs\n" ;

    std::cout << "list: " ;
    std::list<int> lst ;
    std::cout << test_it( lst, values ) << " millisecs\n" ;
}
