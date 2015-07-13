#include <iostream>
#include <cmath>

constexpr unsigned myisqrt_impl(unsigned sq, unsigned dlt, unsigned value) {
    return sq <= value ? myisqrt_impl(sq+dlt, dlt+2, value) : (dlt >> 1) - 1;
}

constexpr unsigned myisqrt(unsigned x) {
    return myisqrt_impl(1, 3, x);
}

constexpr double mysqrt(double x)
{
    double s = x, s0 = 1.0;
    while (std::abs(s-s0) > 1e-15) {
        s0 = s;
        s = 0.5*(s + x/s);
    }
    return s;
}


int main() {
    std::cout << mysqrt(25.0) << std::endl;
    std::cout << mysqrt(39.98) << std::endl;
    std::cout << myisqrt(16) << std::endl; 
    std::cout << myisqrt(18) << std::endl;  
}
