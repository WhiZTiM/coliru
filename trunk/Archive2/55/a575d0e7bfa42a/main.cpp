#include <iostream>
#include <type_traits>

template< typename T > void my_function( T v )
{
    using type = typename std::decay<T>::type ;
    constexpr bool is_int = std::is_same<type,int>::value ;
    constexpr bool is_float = std::is_same<type,float>::value ;

    // common part

    if(is_int) std::cout << "one_liner for int " << v << '\n' ; // one-liner for int

    else if(is_float) std::cout << "one_liner for float " << v << '\n' ; // one-liner for float

    else if( std::is_arithmetic<T>::value ) std::cout << "an arithmetic type other than int or float\n" ;

    else std::cout << "what is this?\n" ; // some other type

    // common part
}

int main()
{
    my_function(4) ; // int
    int i = 5 ; my_function< const int& >(i) ; // int
    my_function( 6.7f ) ; // float
    my_function( 8.9 ) ; // other arithmetic type
    my_function( "hello" ) ; // what is this?
}
