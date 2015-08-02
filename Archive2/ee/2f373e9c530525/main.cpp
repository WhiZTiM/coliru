#include <iostream>
#include <algorithm>
 
int main() 
{
    const int N = 5;
    int digits[N] = {5,4,3,2,1};
 
    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: " << std::is_sorted( digits+N,digits) << '\n';
 
    std::sort(digits, digits+N);
 
    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: " << std::is_sorted(digits, digits+N) << '\n';
}