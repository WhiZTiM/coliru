#include <utility>

namespace carefully {
    using std::move;
    
    template< typename t >
    t const && move( t const & ) = delete;
}

const int k = 3;

int a = carefully::move( 5 ),
    b = carefully::move( a ),
    c = carefully::move( k ),
    d = carefully::move( std::move( k ) );
