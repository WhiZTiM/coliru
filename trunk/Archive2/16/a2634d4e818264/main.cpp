#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

int main()
{
    mp::cpp_int u_100 = 1;
    for(unsigned i = 1; i <= 100; ++i)
        u_100 *= i;

    mp::cpp_int u_99 = 1;
    for(unsigned i = 1; i <= 99; ++i)
        u_99 *= i;

    std::cout << " Walla big numbers! " << std::endl;
    std::cout << std::setw(15) << " 99! = " << u_99 << std::endl;
    std::cout << std::setw(15) << "100! = " << u_100 << std::endl;
    std::cout << std::setw(15) << "100! - 99! = " << (u_100 - u_99) << std::endl;
}
