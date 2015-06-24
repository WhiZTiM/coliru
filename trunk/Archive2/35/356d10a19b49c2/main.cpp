#include <iostream>
#include <type_traits>

template < typename T, typename MEMBER > // (1)
typename std::enable_if< std::is_member_object_pointer< MEMBER T::* >::value >::type
test( const MEMBER T::* )
{
    std::cout << "(1) pointer to const member object\n" ;
}

template < typename T, typename MEMBER > // 2
typename std::enable_if< std::is_member_object_pointer< MEMBER T::* >::value >::type
test( MEMBER T::* )
{
    std::cout << "(2) pointer to non-const member object\n" ;
    // note: (1) is a better match than (2) for 'pointer to const member object'
}

template < typename T, typename MEMBER > // (3)
typename std::enable_if< std::is_member_function_pointer<MEMBER T::*>::value >::type
test( MEMBER T::* )
{
    std::cout << "(3) pointer to member function\n" ;
}

int main()
{
    struct example
    {
        int non_const_member_object = 0 ;
        const int const_member_object = 2 ;
        void member_function(int) {}
    };

    test( &example::non_const_member_object ) ; // (2) pointer to non-const member object
    test( &example::const_member_object ) ; // (1) pointer to const member object
    test( &example::member_function ) ; // (3) pointer to member function
}
