#include <range/v3/all.hpp>
#include <iostream>
#include <vector>

int main() 
{
    using namespace ranges;

    auto const N = 10;
    std::vector<int> v; 
    v.reserve(N);
    
    v |= action::push_back(view::iota(0, N)); 
    random_shuffle(v);
    copy(v, ostream_iterator<>(std::cout, ","));
}
    