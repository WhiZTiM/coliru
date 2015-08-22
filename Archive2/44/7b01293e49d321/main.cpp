#include <iostream>

struct A
{
    A() = default ;
    A( const A& ) { std::cout << "copy constructor" ; }
    A( A&& ) noexcept { std::cout << "move constructor" ; }
    A& operator = ( const A& ) = default ;
    A& operator = ( A&& ) noexcept = default ;
    ~A() = default ;
};

void f( A ) {}
#define CALL_F(arg) ( ( std::cout << "f( " #arg << " ): " ), f(arg), ( std::cout << '\n' ) )

A foo()  { A a ; return a ; }
const A& bar() { static A a ; return a ; }

A&& baz()
{
    static const std::size_t N = 1000 ;
    static A a[N] ;
    static std::size_t n_calls = 0 ;

    if( n_calls < N ) return std::move( a[ n_calls++ ] ) ;
    else throw "too many calls" ;
}

int main()
{
    A a ;
    CALL_F(a) ; // lvalue: copy constructor
    CALL_F( A{} ) ; // prvalue: copy elison
    CALL_F( foo() ) ; // prvalue: copy elision
    CALL_F( bar() ) ; // lvalue: copy constructor
    CALL_F( std::move(a) ) ; // xvalue: move constructor
    CALL_F( baz() ) ; // xvalue: move constructor
}
