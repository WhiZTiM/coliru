#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main()
{
    std::vector<int> data {1, 1, 1, 3, 3, 3, 3, 8, 8};
    std::vector<int> unique;
    //http://en.cppreference.com/w/cpp/algorithm/unique_copy
    std::unique_copy(data.begin(), data.end(), std::back_inserter(unique));

    std::vector<std::pair<int, int>> frequency;
    for(int i: unique)
        //http://en.cppreference.com/w/cpp/algorithm/count
        frequency.emplace_back(i, std::count(data.begin(), data.end(), i));

    for(const auto& e: frequency)
        std::cout << "Element " << e.first << " encountered " << e.second << " times\n";
}
