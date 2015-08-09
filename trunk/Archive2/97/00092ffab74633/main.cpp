#include <tuple>
#include <iostream>

namespace std {
// Helper; could be folded into members of tuple, pair, and array.
template< typename >
struct is_tuple_like : false_type {};

template< typename ... t >
struct is_tuple_like< std::tuple< t ... > > : true_type {};

// Stop ADL from causing infinite template recursion.
template< bool >
struct get_lookup;

template<>
struct get_lookup< false > {
    template< std::size_t i, typename t >
    using result_type = decltype( get< i >( declval< t >() ) );
};

// Overload enables std::get syntax to find user's ADL.
template< size_t i, typename t >
typename get_lookup< is_tuple_like< decay_t< t > >::value >::template result_type< i, t >
get( t && o ) {
    return get< i >( forward< t >( o ) );
}

}

namespace lib {
    struct seq {};
    
    template< std::size_t i >
    std::size_t get( seq ) { return i; }
}

int main() {
    auto t = std::make_tuple( "hello" );
    std::cout << std::get< 0 >( t ) << ' ' << std::get< 42 >( lib::seq{} ) << '\n';
}
