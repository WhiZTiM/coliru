#include <type_traits>
#include <complex>
template<class> struct IsComplex : std::false_type {};
template<class T> struct IsComplex<std::complex<T>> : std::true_type {};

/**
 * Evaluates to a true type if the given complex type is an Array of Structs, false otherwise
 * Defaults to false for Real values
 */
template< typename T, bool T_isComplex = IsComplex<T>::value >
struct IsAoS: std::false_type{};

/**
 * Undefined for (unknown) complex types
 */
template< typename T >
struct IsAoS< T, true >;

template< typename T >
struct IsAoS< std::complex<T> >: std::true_type{};


int main() {
    static_assert(!IsAoS<int>::value , "");
    static_assert(IsAoS<std::complex<double>>::value , "");
    return 0;
}