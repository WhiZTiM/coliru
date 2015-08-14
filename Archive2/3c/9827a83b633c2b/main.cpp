#include <iostream>
#include <set>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& range)
{
    for (auto& el : range)
        os << el << ' ';
    return os;
}

int main()
{
    int input[10]{5, 6, 1, 1, 3, 2, 5, 7, 1, 2};    //because you like raw arrays, I guess?
    
    std::set<int> result(std::cbegin(input), std::cend(input));
    
    std::cout << result << std::endl;
    std::cout << result.size();
}