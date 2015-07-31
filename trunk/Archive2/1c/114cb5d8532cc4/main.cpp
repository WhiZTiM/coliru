#include <iostream>
#include <limits>
#include <float.h>

#define MY_MACRO(){std::cout<<value;}

int main()
{
    std::cout << std::numeric_limits<double>::max() << std::endl;
    std::cout << DBL_MAX << std::endl;
    std::cout << (int) std::numeric_limits<double>::max() << std::endl;
    std::cout << (int) DBL_MAX << std::endl;
}