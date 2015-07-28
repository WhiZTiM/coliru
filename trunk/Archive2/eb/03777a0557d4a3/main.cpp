#include <vector>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

int main()
{
    std::vector<std::string> vec{"Bergmann", "Union Export", "Fiege"};
    for (auto& beer : vec) // access as reference to change a value
    {
        std::for_each(begin(beer), end(beer),
            [](char& c) { c = std::toupper(c); });
    }
    // access as const-ref to avoid copying
    for (const auto& beer : vec) std::cout << beer << '\n';
    for (auto x : { 11,22,33,44,55,66,77 }) std::cout << x << '\n';
}