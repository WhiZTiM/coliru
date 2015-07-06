#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

std::string random_string() // generate a random string
{
    static char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                             ",./<>?;':\"[]\\{}|!@#$%^&*()_+-=`~" ;
    static constexpr std::size_t ALPHABET_SIZE = sizeof(alphabet) - 1 ;
    static std::mt19937 rng( std::random_device{}() ) ;
    static std::uniform_int_distribution<int> distribution( 10, ALPHABET_SIZE ) ;

    const auto sz = distribution(rng) ;
    std::shuffle( alphabet, alphabet+ALPHABET_SIZE, rng ) ;
    return { alphabet, alphabet+sz } ;
}

// insert a string maintaining sorted order
template < typename A, template<typename,typename> class CNTR >
void insert( CNTR< std::string, A >& sorted_seq, const std::string& v ) // invariant: sorted
{
    auto iter = std::begin(sorted_seq) ;
    while( iter != std::end(sorted_seq) && v < *iter ) ++iter ;
    sorted_seq.insert( iter, v ) ;
}

// erase the number at the middle of the sequence, maintaining sorted order
template < typename A, template<typename,typename> class CNTR >
void erase( CNTR< std::string, A >& seq ) // invariant: !empty()
{
    auto iter = std::begin(seq) ;
    const auto n = seq.size() / 2 ;
    for( std::size_t i = 0 ; i < n ; ++i ) ++iter ;
    seq.erase(iter) ;
}

template < typename A, template<typename,typename> class CNTR >
auto test_it( CNTR< std::string, A >& seq, const std::vector<std::string>& values )
{
    const auto start = std::clock() ;
    for( const auto& v : values ) insert( seq, v ) ;
    while( seq.size() > values.size()/2 ) erase(seq) ;
    return ( std::clock() - start ) * 1000.0 / CLOCKS_PER_SEC ;
}

int main()
{
    constexpr std::size_t N = 16'000 ;
    std::vector<std::string> values(N) ;
    std::generate( std::begin(values), std::end(values), random_string ) ;

    std::cout << "vector: " ;
    std::vector<std::string> vec ;
    std::cout << std::setw(5) << test_it( vec, values ) << " millisecs\n" ;

    std::cout << "  list: " ;
    std::list<std::string> lst ;
    std::cout << std::setw(5) << test_it( lst, values ) << " millisecs\n" ;
}
