#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    std::vector<int> foo = {1,2,3,4,5,5,5,5,6,7,8,9};
    auto it = foo.begin();
    while(it != foo.end())
    {
        if (*it == 5)
            it = foo.erase(it);
        else
            ++it;
    }
    for (const auto & e : foo)
        std::cout << e << " ";
    return 0;
}