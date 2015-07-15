#include <iostream>
#include <math.h>

template<int X, int P>
struct Pow
{
    enum { result = X*Pow<X,P-1>::result };
};
template<int X>
struct Pow<X,0>
{
    enum { result = 1 };
};
template<int X>
struct Pow<X,1>
{
    enum { result = X };
};

template <int PRECISION>
float roundP(float f)
{
    const int temp = Pow<10,PRECISION>::result;
    return round(f*temp)/temp;
}

main () {
    std::cout << roundP<0>(M_PI) << std::endl;
    std::cout << roundP<1>(M_PI) << std::endl;
    std::cout << roundP<2>(M_PI) << std::endl;
    std::cout << roundP<3>(M_PI) << std::endl;
    std::cout << roundP<4>(M_PI) << std::endl;
    std::cout << roundP<5>(M_PI) << std::endl;
    std::cout << roundP<6>(M_PI) << std::endl;
    std::cout << roundP<7>(M_PI) << std::endl;
}