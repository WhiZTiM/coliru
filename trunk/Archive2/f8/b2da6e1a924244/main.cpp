#include <range/v3/all.hpp>
#include <vector>
#include <iostream>

int main(int argc, const char* argv[])
{
    std::vector<int> input={1,2,3,4,5,6,7,8,9};
    const int N = 4;
    for (auto&& e: input | ranges::view::take(N))
        std::cout << e << std::endl;
}