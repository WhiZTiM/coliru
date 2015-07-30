#include <tuple>

template< typename t >
constexpr bool is_tuple = false;

template< typename ... elem >
constexpr bool is_tuple< std::tuple< elem ... > > = true;

template< std::size_t ... index, typename alloc, typename target, typename ... arg >
void construct_by_tuple( std::index_sequence< index ... >, alloc al, target & o, std::tuple< arg ... > && a )
     { std::allocator_traits< alloc >::construct( al, & o, std::get< index >( std::move( a ) ) ... ); }

template< typename alloc, typename target, typename ... arg >
void construct_by_tuple( alloc const & al, target & o, std::tuple< arg ... > && a )
    { return construct_by_tuple( std::make_index_sequence< sizeof ... (arg) >{}, al, o, std::move( a ) ); }


// Should upgrade to “&&” fold expression
template< bool ... cond >
struct logical_intersection
    : std::true_type {};
template< bool ... cond >
struct logical_intersection< true, cond ... >
    : logical_intersection< cond ... >::type {};
template< bool ... cond >
struct logical_intersection< false, cond ... >
    : std::false_type {};

// Should upgrade to “,” fold expression
typedef int unpack_evaluate[];

struct internal_tag {};

template< typename ... elem >
struct tuple : std::tuple< elem ... > {

template< typename ... tuples,
    std::enable_if_t< logical_intersection< is_tuple< tuples > ... >::value > * = nullptr >
tuple( std::piecewise_construct_t, tuples ... t )
    : tuple( std::allocator_arg, std::allocator<char>{}, std::piecewise_construct, std::move( t ) ... )
    {}

template< typename alloc, typename ... tuples,
    std::enable_if_t< logical_intersection< is_tuple< tuples > ... >::value > * = nullptr >
tuple( std::allocator_arg_t, alloc const & a, std::piecewise_construct_t, tuples ... t )
    : tuple( internal_tag{}, std::make_index_sequence< sizeof ... (t) >{}, a, std::move( t ) ... )
    {}

template< std::size_t ... index, typename alloc, typename ... tuples,
    std::enable_if_t< logical_intersection< is_tuple< tuples > ... >::value > * = nullptr >
tuple( internal_tag, std::index_sequence< index ... >, alloc const & a, tuples ... t ) {
    (void) unpack_evaluate{( construct_by_tuple( a, std::get< index >( * this ), std::move( t ) ), 0 ) ... };
}
};

#include <iostream>

struct a {
    a() = default;
    a( int i, int j ) { std::cout << "a( " << i << ", " << j << " )\n"; }
    a( a && ) = delete;
};
struct b {
    b() = default;
    b( int i, int j ) { std::cout << "b( " << i << ", " << j << " )\n"; }
    b( b && ) = delete;
};

tuple< a, b > q { std::piecewise_construct, std::forward_as_tuple( 1, 2 ), std::forward_as_tuple( 5, 42 ) };

int main() {}