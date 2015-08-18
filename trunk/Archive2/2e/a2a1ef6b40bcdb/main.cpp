#include <cmath>
#include <iostream>
int main()
{
    std::cout << std::fixed
              << "trunc(+2.7) = " << std::trunc(+2.7) << '\n'
              << "trunc(-3.9) = " << std::trunc(-3.9) << '\n'
              << "trunc(-0.0) = " << std::trunc(-0.0) << '\n'
              << "trunc(-Inf) = " << std::trunc(-INFINITY) << '\n';
}