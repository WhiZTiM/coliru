#include <boost/range/algorithm/sort.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/join.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <vector>

template <typename Cont>
void print_vec(const Cont & v)
{
    for (const auto & i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}

int main(int, const char*[])
{
    auto a = std::vector<int>{7, 8, 9};
    auto b = std::vector<int>{4, 5, 6};
    auto c = std::vector<int>{1, 2, 3};
    
    auto r1 = boost::join(a, b);
    auto r2 = boost::join(r1, c);
    boost::sort(r2);
    
    print_vec(a);
    print_vec(b);
    print_vec(c);
    print_vec(r2);

    return 0;
}
