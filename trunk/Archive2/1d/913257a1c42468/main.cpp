#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>

std::string random_string( std::size_t min_sz, std::size_t max_sz  )
{
    static std::mt19937 rng( std::time(nullptr) ) ;
    static std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" ;
    static std::uniform_int_distribution<std::size_t> distr( min_sz, max_sz ) ;

    std::shuffle( std::begin(alphabet), std::end(alphabet), rng ) ;
    return alphabet.substr( 0, distr(rng) ) ;
}

static std::vector<std::string> rand_str ;

struct A { std::string a, b, c, d, e ; };

void make_A_ref( A& a )
{
    static std::size_t i = 0 ;
    if( i > ( rand_str.size() - 12 ) ) i = 0 ;
    else i += 5 ;
    // modify object passed by reference
    a.a = rand_str[i] ;
    a.b = rand_str[i+1] ;
    a.c = rand_str[i+2] ;
    a.d = rand_str[i+3] ;
    a.e = rand_str[i+4] ;
}

A make_A_value()
{
    static std::size_t i = 0 ;
    if( i > ( rand_str.size() - 12 ) ) i = 0 ;
    else i += 5 ;
    // return value
    return A{ rand_str[i], rand_str[i+1], rand_str[i+2], rand_str[i+3], rand_str[i+4] } ;
}
void vec_a_ref( std::vector<A>& seq, std::size_t n )
{
    seq.clear() ; // modify object passed by reference
    while( seq.size() != n )
    {
        A a ;
        make_A_ref(a) ; // pass reference
        seq.push_back(a) ;
    }
}

std::vector<A> vec_a_value( std::size_t n )
{
    std::vector<A> seq ;
    while( seq.size() != n ) seq.push_back( make_A_value() ) ; // return value
    return seq ; // return value
}

int main()
{
     constexpr std::size_t N_RANDOM_STRINGS = 50'021 ;
     constexpr std::size_t N_OBJECTS = 1'000'000 ;

     rand_str.reserve(N_RANDOM_STRINGS) ;
     while( rand_str.size() != N_RANDOM_STRINGS )
        rand_str.push_back( random_string( 50, 100 ) ) ;

     int r = 0 ;

     {
         const auto start = std::clock() ;
         std::vector<A> seq ;
         vec_a_ref( seq, N_OBJECTS ) ;
         const auto end = std::clock() ;
         std::cout << "use pass by reference everywhere: " << double(end-start) / CLOCKS_PER_SEC << " seconds.\n" ;
         r += seq.back().a.size() ;
     }

     {
         const auto start = std::clock() ;
         std::vector<A> seq = vec_a_value(N_OBJECTS) ;
         const auto end = std::clock() ;
         std::cout << "  use value semantics everywhere: " << double(end-start) / CLOCKS_PER_SEC << " seconds.\n" ;
         r += seq.back().a.size() ;
     }
     
     return r != 0 ;
}
