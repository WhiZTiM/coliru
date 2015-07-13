#include <iostream>
#include <cmath>

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
    std::cout << mysqrt(25) << std::endl;
    std::cout << mysqrt(39) << std::endl;
}
