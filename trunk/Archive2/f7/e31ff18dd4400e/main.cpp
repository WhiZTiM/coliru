#include <iostream>

struct A
{
    A() = default ;
    A( const A& ) ;
    A( A&& ) noexcept ;
    A& operator = ( const A& ) = default ;
    A& operator = ( A&& ) noexcept = default ;
    ~A() = default ;
};

A::A( const A& ) { std::cout << "copy constructor" ; }
A::A( A&& ) noexcept { std::cout << "move constructor" ; }

void f( A ) {}
A foo()  { A a ; return a ; }
const A& bar() { static A a ; return a ; }

