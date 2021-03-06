#include <iostream>
#include <stdexcept>
 
// constexpr functions use recursion rather than iteration
constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n-1));
}

template< int n > using int_ = std::integral_constant< int, n >;

template< int n >
constexpr bool issix(int_< n > const) {
    return false;
}
template<>
constexpr bool issix< 6 >(int_< 6 > const) {
    return true;
}

constexpr bool issix(int const n) {
    return issix(int_<factorial(n)>());
}

int main()
{
    std::cout << "issix: " << factorial(4) << ": " << issix(factorial(4)) << '\n';
    return 0;
}