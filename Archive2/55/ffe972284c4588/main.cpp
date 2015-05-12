#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <array>

int main()
{
    constexpr int n = 100000;
    std::array<boost::multiprecision::cpp_int, n> fib1, fib2;
    boost::multiprecision::cpp_int last = 0, next = 1;
    
    int i = 0;
    while (i != n) {
    	fib1[i] = last, last = next, next += fib1.back();
    	++i;
    }
    
    boost::multiprecision::cpp_int sumFib1;
    for (const auto & e : fib1) {
        sumFib1 += e;
    }

	i = 0, last = 0, next = 1;
    while (i != n) {
        fib2[i] = last, last = next, next += fib2.back();
        ++i;
    }
    
    boost::multiprecision::cpp_int sumFib2;
    for (const auto & e : fib2) {
        sumFib2 += e;
    }

    std::cout << sumFib2 - sumFib1 << std::endl;
    
    return 0;
}