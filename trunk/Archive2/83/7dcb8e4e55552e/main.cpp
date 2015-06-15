#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> haystack;
    haystack.push_back(1);
    haystack.push_back(3);
    haystack.push_back(4);
    haystack.push_back(5);
    haystack.push_back(9);
    
    std::vector<int> needles;
    needles.push_back(1);
    needles.push_back(2);
    needles.push_back(3);
 
    for (auto needle : needles) {
        std::cout << "Searching for " << needle << '\n';
        if (std::binary_search(haystack.begin(), haystack.end(), needle)) {
            std::cout << "Found " << needle << '\n';
        } else {
            std::cout << "no dice!\n";
        }
    }
}