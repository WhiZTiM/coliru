#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    int input[10]{5, 6, 1, 1, 3, 2, 5, 7, 1, 2};    //because you like raw arrays, I guess?
    std::cout << "input is: ";
    for(int i : input)
        std::cout << i << " ";
    
    std::vector<int> result(std::cbegin(input), std::cend(input));    
    std::cout << std::endl << "before sorting these, we have: " << result << std::endl;
    std::sort(std::begin(result), std::end(result));
    std::cout << "after sorting these, we have: " << result << std::endl;
    result.erase(std::unique(std::begin(result), std::end(result)), std::end(result));    
    std::cout << "unique numbers are: " << result << std::endl;
}
