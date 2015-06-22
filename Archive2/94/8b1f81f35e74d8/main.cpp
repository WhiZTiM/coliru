#include <range/v3/all.hpp>
#include <iostream>
#include <vector>

int main() 
{
    std::vector<float> rng = {1.2,-1.2,2.3,-2.3};
    auto onlyEvenIndex = [](auto i){ return (i&1) == 0;};

    auto even_indices = ranges::view::iota(0ul, rng.size()) | ranges::view::filter(onlyEvenIndex);
    auto min_ind = *ranges::min_element(even_indices, [&rng](auto L, auto R) { return rng[L] < rng[R]; });
    std::cout << rng[min_ind];
}
