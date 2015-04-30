#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<std::vector<int>> v{{1,1,1},{1,1,1},{1,1,1}};
    std::vector<int> result, tmp;
    for(auto&& elem: v)
    {
        std::set_union(elem.begin(), elem.end(), 
                       result.begin(), result.end(),
                       std::back_inserter(tmp));
        result = std::move(tmp);
    }
    for(auto&& elem: result)
        std::cout << elem << " ";
}