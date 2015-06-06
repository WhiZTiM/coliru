#include <iterator>    // for back_inserter
#include <locale>
#include <string>
#include <algorithm>
#include <cctype>      // old <ctype.h>
#include <iostream>

void findRange(const std::vector<std::pair<int, int>>& endRange, int value)
{
    auto it = std::lower_bound(endRange.begin(), endRange.end(), value, [](const std::pair<int, int>& it, int value) {
        std::cout << it.first << " " << it.second << " " << value << std::endl;
        return it.first <= value;
    });
    
    if (it == endRange.end())
        std::cout << "END" << std::endl;
    else
        std::cout << it->first << " " << it->second << std::endl;
}

int main ()
{
    std::vector<std::pair<int, int>> endRanges;
    endRanges.emplace_back(std::make_pair(10, 1));
    endRanges.emplace_back(std::make_pair(20, 2));
    endRanges.emplace_back(std::make_pair(30, 3));
    endRanges.emplace_back(std::make_pair(40, 4));
    endRanges.emplace_back(std::make_pair(50, 5));
    
    findRange(endRanges, 10);
}