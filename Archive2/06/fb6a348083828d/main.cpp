#include <cstdint>
#include <iostream>

template<typename Tag>
uint32_t get_counter() {
    static uint32_t counter = 0;
    return counter++;
}

template<typename T, typename U>
struct thing {
    static const uint32_t counter;
};

template<typename T, typename U>
const uint32_t thing<T, U>::counter(get_counter<T>());

// global scope
struct X {};
struct Y {};

int main()
{
    // function scope
    struct Z{};

    uint x0 = thing<X, int>::counter;
    uint x1 = thing<X, double>::counter;
    uint x2 = thing<X, double>::counter;
    uint x3 = thing<X, std::string>::counter;
    uint x4 = thing<X, int>::counter;
    uint x5 = thing<X, int>::counter;

    std::cout << x0 << ", " << x1 << ", " << x2 << ", "
              << x3 << ", " << x4 << ", " << x5 << std::endl;

    uint y0 = thing<Y, int>::counter;
    uint y1 = thing<Y, double>::counter;
    uint y2 = thing<Y, double>::counter;
    uint y3 = thing<Y, std::string>::counter;
    uint y4 = thing<Y, int>::counter;
    uint y5 = thing<Y, int>::counter;

    std::cout << y0 << ", " << y1 << ", " << y2 << ", "
              << y3 << ", " << y4 << ", " << y5 << std::endl;

    uint z0 = thing<Z, int>::counter;
    uint z1 = thing<Z, double>::counter;
    uint z2 = thing<Z, double>::counter;
    uint z3 = thing<Z, std::string>::counter;
    uint z4 = thing<Z, int>::counter;
    uint z5 = thing<Z, int>::counter;

    std::cout << z0 << ", " << z1 << ", " << z2 << ", "
              << z3 << ", " << z4 << ", " << z5 << std::endl;

    return 0;
}