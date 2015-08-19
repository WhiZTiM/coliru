#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
 
int main() {
    std::string const s1 { "abcdef" };
    std::string const s2 { "abcdEF" };
    std::cout << std::boolalpha;
    std::cout << std::equal(begin(s1), end(s1), begin(s2), end(s2)) << std::endl;
    std::cout << std::equal(begin(s1), end(s1), begin(s2), end(s2),
        [](auto lhs, auto rhs){ return std::toupper(lhs) == std::toupper(rhs); }) 
        << std::endl;
}