#include <algorithm>
#include <iostream>
#include <random>
#include <functional>
#include <climits>
 
int main()
{
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(1, 6);
    std::vector<int> v(5);
    std::generate(v.begin(), v.end(), std::bind(distribution, generator)); // Using the C function rand()
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
 
    // Initialize with default values 0,1,2,3,4 from a lambda function
    // Equivalent to std::iota(v.begin(), v.end(), 0);
    int n(0);
    std::generate(v.begin(), v.end(), [&]{ return n++; }); 
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
}