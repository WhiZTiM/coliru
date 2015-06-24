#include <iostream>
#include <type_traits>

template < typename T, typename MEMBER >
typename std::enable_if< std::is_member_object_pointer< MEMBER T::* >::value >::type
test( MEMBER T::* )
{
    std::cout << "pointer to const member object\n" ;
}

template < typename T, typename MEMBER >
typename std::enable_if< std::is_member_object_pointer< MEMBER T::* >::value >::type
test( const MEMBER T::* )
{
    std::cout << "pointer to (non-const) member object\n" ;
}

template < typename T, typename MEMBER >
typename std::enable_if< std::is_member_function_pointer<MEMBER T::*>::value >::type
test( MEMBER T::* )
{
    std::cout << "pointer to member function\n" ;
}

int main()
{
    struct example
    {
        int non_const_member_object = 0 ;
        const int const_member_object = 2 ;
        void member_function(int) {}
    };

    test( &example::non_const_member_object ) ;
    test( &example::const_member_object ) ;
    test( &example::member_function ) ;
}
