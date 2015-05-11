#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>

int main() {
    std::vector<boost::multiprecision::cpp_int> fib1, fib2;
    boost::multiprecision::cpp_int last = 0, next = 1;
    
    int n = 100000;
    
    int i = 0;
    while (i != n) {
        fib1.push_back(last);
        last  = next;
        next += last;
        ++i;
    }

	i = 0, last = 0, next = 1;
    while (i != n) {
        fib2.push_back(last);
        last  = next;
        next += last;
        ++i;
    }
    
    boost::multiprecision::cpp_int sumFib1;
    for (auto && e : fib1) {
        sumFib1 += e;
    }

    boost::multiprecision::cpp_int sumFib2;
    for (auto && e : fib2) {
        sumFib2 += e;
    }

    std::cout << sumFib2 - sumFib1 << std::endl;
}