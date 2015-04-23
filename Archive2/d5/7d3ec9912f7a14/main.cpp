#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
 
int main()
{
    std::string s1 = "mississippi river";
    std::cout << "before: " << s1 << '\n';
    auto st = std::set<char>(begin(s1), end(s1));
    std::string s2;
    std::unique_copy(s1.begin(), s1.end(), std::back_inserter(s2));
 
    for (auto x : st) std::cout << x;
    std::cout << std::endl;
}