#include <iostream>
#include <omp.h>
#include <ctime>
#include <type_traits>

template<size_t N>
struct fibonacci : std::integral_constant<size_t, fibonacci<N-1>{} + fibonacci<N-2>{}> {};

template<> struct fibonacci<1> : std::integral_constant<size_t,1> {};
template<> struct fibonacci<0> : std::integral_constant<size_t,0> {};


int main() {
    const size_t N = 4000;
    
    {
    clock_t start = clock();
    std::cout <<  "Fibonacci(" << N << ") = " << fibonacci<N>() << std::endl;
    std::cout << "Time : " << (double)(clock() - start)/CLOCKS_PER_SEC << " s" << std::endl;
    }
}

