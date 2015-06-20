#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>

    template< typename I, typename F >
    std::enable_if_t< std::is_integral< I >::value && std::is_floating_point< F >::value,
    bool > less( I i, F f ) {
        // Return early for operands of different signs.
        if ( i < 0 != f < 0 ) return i < 0;

        bool rev = i >= 0;
        if ( rev ) {
            f = - f; // Make both operands non-positive.
            i = - i; // (Negativity avoids integer overflow here.)
        }
    
        if ( f < /* (F) */ std::numeric_limits<I>::min() ) {
            // |i| < |f| because f is outside the range of I.
            std::cout << "outside integer range ";
            return rev;
        }
        if ( f * std::numeric_limits<F>::epsilon() <= -1 ) {
            // f must be an integer (in I) because of limited precision in F.
            std::cout << "imprecisely in integer range ";
            I fi = f;
            return rev? fi < i : i < fi;
        }
        // |f| has better than integer precision.
        // If (F) |i| loses precision, it will still be greater than |f|.
        std::cout << "native comparison ";
        return rev? f < i : i < f;
    }

template< typename I, typename F >
void compare_comparisons( I i, F f ) {
    std::cout << i << " < " << f << ", builtin " << ( i < f ) << ", special " << less( i, f ) << '\n';
}

int main() {
    std::cout << std::boolalpha << std::setprecision(20) << '\n';
    compare_comparisons( std::numeric_limits<int>::max(), (float) std::numeric_limits<int>::max() );
    compare_comparisons( std::numeric_limits<int>::min(), (float) std::numeric_limits<int>::min() );
    compare_comparisons( std::numeric_limits<int>::min() + 448, (float) std::numeric_limits<int>::min() + 500 );
    compare_comparisons( std::numeric_limits<int>::min(), (float) std::numeric_limits<int>::min() - 500 );
    compare_comparisons( - ( 1 << 24 ) - 1, - (float) ( 1 << 24 ) );
    compare_comparisons( ( 1 << 25 ) - 1, (float) ( 1 << 25 ) );
    compare_comparisons( ( 1 << 23 ) - 1, (float) ( ( 1 << 23 ) ) );
    compare_comparisons( ( 1 << 23 ) - 1, (float) ( ( 1 << 23 ) - 1 ) );
    compare_comparisons( - ( 1 << 23 ) - 1, - (float) ( 1 << 23 ) );
    compare_comparisons( - ( 1 << 23 ), - (float) ( 1 << 23 ) + 1 );
    compare_comparisons( - ( 1 << 23 ) + 1, - (float) ( 1 << 23 ) );
}
