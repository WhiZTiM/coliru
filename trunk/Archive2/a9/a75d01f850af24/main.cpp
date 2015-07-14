#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    std::vector<int> foo = {1,2,3,4,5,5,5,5,6,7,8,9};
    std::remove_if(foo.begin(), foo.end(), [](int i){ if(i == 5) return true; else return false; });
    for (const auto & e : foo)
        std::cout << e << " ";
}