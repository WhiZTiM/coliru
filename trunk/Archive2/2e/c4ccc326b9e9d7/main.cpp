#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
 
int main()
{
    // construction uses aggregate initialization
    std::array<int, 3> a1{ {1, 2, 3} }; // double-braces required in C++11 (not in C++14)
    //std::array<int, 3> a2 = {1, 2, 3};  // never required after =
    std::array<std::string, 3> a3 = { std::string("a"), "b", "c" };
 
    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a3.begin(), a3.end(), 
                      std::ostream_iterator<std::string>(std::cout, " "));
 
    std::cout << '\n';
 
    // ranged for loop is supported
    for(const auto& s: a3)
        std::cout << s << ' ';
}