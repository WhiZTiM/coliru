#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/detail/default_ops.hpp>
#include <boost/multiprecision/number.hpp>
#include <iostream>

namespace {
    namespace bmp = boost::multiprecision;
    
    template <int N> bmp::number<bmp::cpp_dec_float<N> > const my_const_pi 
        = bmp::default_ops::get_constant_pi<bmp::cpp_dec_float<N> >();
}

int main() {
    std::cout << std::setprecision(50)   << my_const_pi<50>   << "\n";
    std::cout << my_const_pi<5000> << "\n";
}

