#include <iostream>
#include <cstdlib>
#include <random>
#include <iomanip>

static const int N = 16'000'000 ;
static const int M = 6 ;

template < typename FN >
void test_it( const char* label, FN&& fn )
{
    std::cout << label << ":\n\n" ;
    int freq[M] {} ;
    for( int i = 0 ; i < N ; ++i ) ++freq[ fn() ] ;
    for( int i = 0 ; i < M ; ++i )
        std::cout << i << ". " << freq[i] << ' ' << double(freq[i]*100) / N << " %\n" ;
    std::cout << "\n-------------\n\n" ;
}

int main()
{
    const auto seed = std::random_device{}() ;
    std::srand(seed) ;
    std::mt19937 rng(seed) ;

    // warm up
    for( std::size_t i = 0 ; i < rng.state_size ; ++i ) std::rand() ;
    rng.discard( rng.state_size ) ;

    std::uniform_int_distribution<int> distr( 0, M-1 ) ;

    std::cout << std::fixed << std::setprecision(2) ;

    const auto legacy = [] { return std::rand() % M ; } ;
    const auto current = [&] { return distr(rng) ; } ;

    test_it( "std::rand() % M", legacy ) ;
    test_it( "mt19937, uniform int distribution", current ) ;
}
