#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>

struct s
{
    double x;
    int y;
};

template<typename Container, typename T, typename M>
std::vector<M> select_mem(Container const& c, M T::* mem)
{
    std::vector<M> result;
    result.reserve(c.size());
    
    std::transform(c.begin(), c.end(), std::back_inserter(result),
                   std::mem_fn(mem));
    return result;
}

template<typename Container, typename Indices, typename T, typename M>
std::vector<M> select_mem(Container const& c, Indices const& ind, M T::* mem)
{
    std::vector<M> result;
    result.reserve(ind.size());
    
    std::transform(ind.begin(), ind.end(), std::back_inserter(result),
                   [&c, mem](typename Indices::value_type const& i) {
                       return std::mem_fn(mem)(c[i]);
                   });
    return result;
}

int main()
{
    std::vector<s> v {{10, 1}, {20, 2}, {30, 3}, {40, 4}};
    
    for(auto const& x : select_mem(v, &s::x)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    
    std::vector<int> indices{1,2};
    for(auto const& x : select_mem(v, indices, &s::x)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
