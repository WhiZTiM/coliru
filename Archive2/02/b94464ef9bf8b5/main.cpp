#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <array>

typedef boost::multiprecision::cpp_int big_int;

class GenFibonacci {
    big_int prev1, prev2;
    int count;
public:
    GenFibonacci() : prev1(1), prev2(1), count(1) {}
    big_int next ( ) {
        if (count < 3) return 1;
        big_int current = prev1 + prev2;
        prev1 = prev2;
        prev2 = current;
        return current;
    }
};

int main()
{
    constexpr int n = 100000;
    GenFibonacci fib1, fib2;
    big_int sum1, sum2;
    
    for (int i = 0; i < n; ++i){
        sum1 += fib1.next();
        sum2 += fib2.next();
    }

    std::cout << sum2 - sum1 << std::endl;
    
    return 0;
}