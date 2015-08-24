#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> create_lists(int no_lists, int no_per_list)
{
    std::vector<std::vector<int>> temp(no_lists, std::vector<int>(no_per_list));
    for (auto & e : temp)
        std::transform(e.begin(), e.end(), e.begin(), [](int foo){static int counter = 0; return counter++;});
    return temp;
}
    
int main()
{
    auto foo = create_lists(3,10);
    for (const auto & v : foo)
    {
        for(const auto & e : v)
            std::cout << e << " ";
        std::cout << "\n";
    }
    auto foo2 = create_lists(3,10);
    for (const auto & v : foo2)
    {
        for(const auto & e : v)
            std::cout << e << " ";
        std::cout << "\n";
    }
}