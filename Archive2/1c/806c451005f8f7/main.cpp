#include <type_traits>

int main()
{
    using fn_type = const double* ( const double*, int ) ;
    typedef const double* fn_type( const double*, int ) ; // same as above
    using ptr_to_fn_type = fn_type* ;
    using ref_to_ptr_to_fn_type = ptr_to_fn_type& ;
    using array_of_3_ptr_to_fn_type = ptr_to_fn_type[3] ;
    using ptr_to_array_of_3_ptr_to_fn_type = array_of_3_ptr_to_fn_type* ;

    const double * (*pa[3])(const double *, int) = { /* ... */ };

    // type of pa is 'array of 3 pointers to function'
    static_assert( std::is_same< array_of_3_ptr_to_fn_type, decltype(pa) >::value, "must be same type" ) ;

    // pa[0] yields a reference to first element. pa[1] yields a reference to second element,etc.
    static_assert( std::is_same< ref_to_ptr_to_fn_type, decltype(pa[0]) >::value, "must be same type" ) ;

    // array is implicitly converted to pointer to first element, *pa is reference to first element
    static_assert( std::is_same< ref_to_ptr_to_fn_type, decltype(*pa) >::value, "must be same type" ) ;

    // value category of +pa[0] and +*pa is 'prvalue'. +pa[0]  is a prvalue of type 'pointer to function'
    static_assert( std::is_same< ptr_to_fn_type, decltype( +pa[0] ) >::value, "must be same type" ) ;
    static_assert( std::is_same< ptr_to_fn_type, decltype( +*pa ) >::value, "must be same type" ) ;

    // &pa is the address of the array; type of &pa is pointer to array of 3 pointers to function
    static_assert( std::is_same< ptr_to_array_of_3_ptr_to_fn_type, decltype(&pa) >::value, "must be same type" ) ;
}
