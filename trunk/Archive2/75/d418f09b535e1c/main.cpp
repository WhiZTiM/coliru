#include <iostream>
#include <boost/type_traits/integral_constant.hpp>

template<std::size_t Bits>
struct uint_traits : boost::integral_constant< unsigned
                                             , (Bits == 1 ) ? 1 :
                                               (Bits == 8 ) ? 2 :
                                               (Bits == 16) ? 3 :
                                               (Bits == 32) ? 4 :
                                               (Bits == 64) ? 5 :
                                               throw 0 > {
};

int main () {
    typedef uint_traits<1 > a;
    typedef uint_traits<8 > b;
    typedef uint_traits<16> c;
    typedef uint_traits<32> d;
    typedef uint_traits<64> e;
    typedef uint_traits<24> f;
    
    std::cout << a::value << "\n";
    std::cout << b::value << "\n";
    std::cout << c::value << "\n";
    std::cout << d::value << "\n";
    std::cout << e::value << "\n";
    //std::cout << f::value << "\n"; //ERROR, throw-expression is not a constant expresion
}
