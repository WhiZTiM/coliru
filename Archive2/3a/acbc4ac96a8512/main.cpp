#include <iostream>
#include <vector>
#include <ctime>

struct moveable
{
    moveable( int v = 0, double d = 0 ) : v(16,v), d(16,d) {}

    std::vector<int> v ;
    std::vector<double> d ;
};

template < typename T > struct A
{
    // pass by reference to const and copy into vector
    void push_back_cref( const T& v ) { vec.push_back(v) ; }
    
    // pass by value and move into vector
    void push_back_value( T v ) { vec.push_back( std::move(v) ) ; }
    
    void pop_back() { vec.pop_back() ; }
    std::size_t size() const { return vec.size() ; }

    std::vector<T> vec ;
};

int main()
{
    constexpr int N = 1'000'000 ;

    const moveable lvalue ;

    A<moveable> a ;
    a.vec.reserve(N) ;

    const auto milliseconds = []( std::clock_t v ) { return v * 1000.0 / CLOCKS_PER_SEC ; } ;

    std::cout << "rvalues:\n----------------\n" ;

    auto start = std::clock() ;
    while( a.vec.size() < N ) a.vec.push_back( { 1, 2 } ) ;
    while( a.vec.size() > 0 ) a.vec.pop_back() ;
    std::cout << "   direct access to vector: " << milliseconds( std::clock() - start ) << '\n' ;

    start = std::clock() ;
    while( a.size() < N ) a.push_back_cref( { 1, 2 } ) ;
    while( a.size() > 0 ) a.pop_back() ;
    std::cout << "lvalue reference semantics: " << milliseconds( std::clock() - start ) << '\n' ;

    start = std::clock() ;
    while( a.size() < N ) a.push_back_value( { 1, 2 } ) ;
    while( a.size() > 0 ) a.pop_back() ;
    std::cout << "           value semantics: " << milliseconds( std::clock() - start ) << '\n' ;

    std::cout << "\nlvalues:\n----------------\n" ;

    start = std::clock() ;
    while( a.vec.size() < N ) a.vec.push_back(lvalue) ;
    while( a.vec.size() > 0 ) a.vec.pop_back() ;
    std::cout << "   direct access to vector: " << milliseconds( std::clock() - start ) << '\n' ;

    start = std::clock() ;
    while( a.size() < N ) a.push_back_cref(lvalue) ;
    while( a.size() > 0 ) a.pop_back() ;
    std::cout << "lvalue reference semantics: " << milliseconds( std::clock() - start ) << '\n' ;

    start = std::clock() ;
    while( a.size() < N ) a.push_back_value(lvalue) ;
    while( a.size() > 0 ) a.pop_back() ;
    std::cout << "           value semantics: " << milliseconds( std::clock() - start ) << '\n' ;
}
