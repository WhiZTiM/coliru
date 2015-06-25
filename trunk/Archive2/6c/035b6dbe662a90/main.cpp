#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

void foo(std::vector<int>& vec, const size_t start, const size_t end)
{
    assert(vec.size() >= end-start);
    auto it1 = vec.begin() + start;
    auto it2 = vec.begin() + end;

    std::sort(it1, it2);
}

int main()
{
    std::vector<int> vec{9,8,7,6,5,4,3,2,1};
    foo(vec, 3, 6);
    
    for (auto it : vec)
        std::cout << it << ' ';
    std::cout << '\n';
}