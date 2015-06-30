#include <cmath>
#include <type_traits>

#if s__cplusplus >= 201103

namespace {
    template<int>
    std::true_type test();
    template<int v>
    auto constexpr_log2_test(std::nullptr_t) -> decltype(test<(std::log2(v), 0)>());
    //                                          ^adopts the return type of test
    template<int>
    auto constexpr_log2_test(...) -> std::false_type;
}

template<typename T>
struct has_constexpr_log2 : decltype(constexpr_log2_test<2>(nullptr)) {};

/*
#ifdef __clang__
    static_assert(!has_constexpr_log2<int>::value, "clang");
#else// __GNUC__
    static_assert(has_constexpr_log2<int>::value, "gcc");
#endif
*/

//uses a constexpr std::log2 if available (e.g. gcc4.7+)
template<typename T, typename = typename std::enable_if<has_constexpr_log2<T>::value>::type >
constexpr std::size_t int_log(const T & val) {
    return val == 0 ? 0 : std::ilog2(val);
}

//custom tail recursive constexpr log implementation
template<typename T, typename = typename std::enable_if<!has_constexpr_log2<T>::value>::type>
constexpr T int_log(const T & val, const T & base = 2, const T & res = 0) {
    return val < base ? res : int_log(val/base, base, res+1);
}

#else//no c++11

template<typename>
struct has_constexpr_log2 {
    static const bool value = false;
};

constexpr std::size_t int_log(const std::size_t val, const std::size_t base = 2, const std::size_t res = 0) {
    return val < base ? res : int_log(val/base, base, res+1);
}

#endif

#include <cstdint>

/* http://aggregate.org/MAGIC/#Log2%20of%20an%20Integer */
uint32_t ones32(uint32_t x) {
/* 32-bit recursive reduction using SWAR...
   but first step is mapping 2-bit values
   into sum of 2 1-bit values in sneaky way
*/
    x -= ((x >> 1) & 0x55555555);
    x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
    x = (((x >> 4) + x) & 0x0f0f0f0f);
    x += (x >> 8);
    x += (x >> 16);
    return(x & 0x0000003f);
}

uint32_t log2uint32(uint32_t x) {

    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);

    return(ones32(x >> 1));
}

inline std::size_t ilog2(const std::size_t x) {
    if (x == 0) {
        return 0;
    }
    std::size_t y;
    asm("bsr %1, %0" : "=r"(y) : "r" (x));
    return y;
}

inline std::size_t ilog22(std::size_t x) {
    std::size_t bitcount = 0;
    while (x >>= 1) {
        ++bitcount;
    }
    return bitcount;
}

#include <chrono>
#include <functional>

std::size_t measure(std::function<void()> fkt) {
    auto start = std::chrono::high_resolution_clock::now();
    
    fkt();
    
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
}

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    std::cout << __cplusplus << '\n';
    std::cout << std::boolalpha;
    std::cout << "has_constexpr_log2: " << has_constexpr_log2<int>::value << '\n';
    for (size_t i = 1; i < 100; ++i) {
        auto a = int_log(i);
        auto b = log2uint32(i);
        auto c = ilog2(i);
        assert(a == b && a == c);
    }
    std::cout << "log2uint32: \t";
    for (size_t i = 0; i < 100; ++i) {
        std::cout << log2uint32(i) << ' ';
    }
    std::cout << "\nint_log: \t";
    for (size_t i = 0; i < 100; ++i) {
        std::cout << int_log(i) << ' ';
    }
    std::cout << "\nilog2:\t\t";
    for (size_t i = 0; i < 100; ++i) {
        std::cout << ilog2(i) << ' ';
    }
    std::cout << "\nilog22:\t\t";
    for (size_t i = 0; i < 100; ++i) {
        std::cout << ilog22(i) << ' ';
    }
    std::cout << "\nlog2:\t\t  ";
    for (size_t i = 1; i < 100; ++i) {
        std::cout << static_cast<std::size_t>(std::log2(i)) << ' ';
    }
    std::cout << std::endl;
    
    const int iterations = 1000000;
    std::array<std::vector<std::size_t>, 4> results;
    for (auto & vec : results) {
        vec.resize(iterations);
    }
    std::cout << "log2uint32: \t" << measure([&]{
        for (std::size_t i = 0; i < iterations; ++i) {
            results[1][i] = log2uint32(i);
        }
    }) << '\n';
    std::cout << "int_log: \t" << measure([&]{
        for (std::size_t i = 0; i < iterations; ++i) {
            results[0][i] = int_log(i);
        }
    }) << '\n';
    std::cout << "ilog2: \t\t" << measure([&]{
        for (std::size_t i = 0; i < iterations; ++i) {
            results[2][i] = ilog2(i);
        }
    }) << '\n';
    std::cout << "ilog22: \t" << measure([&]{
        for (std::size_t i = 0; i < iterations; ++i) {
            results[2][i] = ilog22(i);
        }
    }) << '\n';
    std::cout << "std::log2: \t" << measure([&]{
        for (std::size_t i = 0; i < iterations; ++i) {
            results[3][i] = static_cast<std::size_t>(std::log2(i));
        }
    }) << '\n';
}