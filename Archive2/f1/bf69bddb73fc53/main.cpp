#include <range/v3/all.hpp>
#include <iostream>
#include <vector>

int main() 
{
    using namespace ranges;
    
    auto v = view::iota(1, 11) | to_<std::vector<int>>();
    std::cout << view::all(v)  << '\n';
    
    auto rng = v | view::slice(3, 7); 
    std::cout << rng << '\n';
}
