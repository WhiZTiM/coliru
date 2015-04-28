#include <iostream>
#include <utility>
#include <string>

template< typename T, std::size_t N > void assign( T(&arr)[N], std::size_t pos, const T& value )
{ if( pos < N ) arr[pos] = value ; /* copy assign lvalue*/ }

template< typename T, std::size_t N > void assign( T(&arr)[N], std::size_t pos, T&& value )
{ if( pos < N ) arr[pos] = std::move(value) ; /* move assign rvalue*/ }

template< typename T, std::size_t N > void assign_v2( T(&arr)[N], std::size_t pos, T value )
{ if( pos < N ) arr[pos] = std::move(value) ; /* move assign parameter passed by value*/ }

struct A
{
    A() = default ;
    A( const char* cstr ) : str(cstr) {}

    A( const A& that ) : str(that.str)
    { std::cout << "copy construct\n" ; }

    A( A&& that ) noexcept : str( std::move(that.str) )
    { str.swap(that.str) ; std::cout << "move construct\n" ; }

    A& operator= ( const A& that )
    { str = that.str ; std::cout << "copy assign\n" ; return *this ; }

    A& operator= ( A&& that ) noexcept
    { str.swap(that.str) ; std::cout << "move assign\n" ; return *this ; }

    std::string str ;
};

int main()
{
    A arr[20] ; // 20 strings are default-constructed
    A hello( "hello" ) ;

    assign( arr, 0, hello ) ; // lvalue, copy assign
    std::cout << "------------\n" ;
    // hello can still be used here

    assign( arr, 1, A( " world!" ) ) ; // rvalue, move assign
    std::cout << "------------\n" ;

    assign_v2( arr, 2, hello ) ; // lvalue, copy construct, followed by move assign the copy
    std::cout << "------------\n" ;

    assign_v2( arr, 3, A( " world!" ) ) ; // rvalue, move assign (copy elision)
    std::cout << "------------\n" ;
}
