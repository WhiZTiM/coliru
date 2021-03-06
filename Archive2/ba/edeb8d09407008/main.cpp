#include <iostream>
#include <stdexcept>
#include <cassert>

template < typename T > struct bounded_range
{

    constexpr bounded_range( const T& lb, const T& ub, const T& v = T() )
        : lbound(lb), ubound(ub), value( check_bounds(v) ) {}

    constexpr operator const T& () const { return value ; }

    bounded_range<T>& operator= ( const T& v ) { value = check_bounds(v) ; return *this ; }

    // operator ++ etc.

    const T lbound ;
    const T ubound ;

    private:
        T value ;

        constexpr const T& check_bounds( const T& v )
        { return v < lbound || v >= ubound ? ( assert(false), throw std::out_of_range("out of range"), v ) : v ; }
};

using brint = bounded_range<int> ;

int main()
{
    try
    {
        brint i( 10, 20, 15 ) ;
        std::cout << i << '\n' ;
        i = i + 3 ;
        std::cout << i << '\n' ;
        i = i + 2 ;
        std::cout << i << '\n' ;
    }
    catch( const std::out_of_range& ) { std::cerr << "out of range\n" ; }

    try { brint j( 10, 20, 25 ) ; std::cout << j << '\n' ; }
    catch( const std::out_of_range& ) { std::cerr << "out of range\n" ; }

}
