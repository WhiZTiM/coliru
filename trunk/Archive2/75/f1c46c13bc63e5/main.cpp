#include <iostream>

struct A
{
    template < typename PTR_MEM_FUN, typename... ARGS >
    auto outer_function( PTR_MEM_FUN ptr_mem_fun, ARGS... args ) // simple pass by value
    { return (this->*ptr_mem_fun)( args... ) ; }

    void foo( int a, double b ) { std::cout << "A::foo(" << a << ',' << b << ")\n" ; v += a+b ;  }
    int bar( const char* msg ) const { std::cout << "A::bar('" << msg << "')\n" ; return v ;  }
    double baz() const { std::cout << "A::baz()\n" ; return v * 1.2 ;  }

    int v = 0 ;
};

int main()
{
    A a ;
    a.outer_function( &A::foo, 1, 2.3 ) ;
    a.outer_function( &A::bar, "hello" ) ;
    a.outer_function( &A::baz ) ;
}
