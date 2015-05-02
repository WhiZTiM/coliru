#include <boost/range/algorithm/sort.hpp>
#include <boost/range/join.hpp>
#include <iostream>
#include <iterator>
#include <vector>

template <typename C>
void print_vec(const C & v)
{
    for (const auto & i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}

template <typename C>
auto join(C && c)
{
    return boost::make_iterator_range(std::begin(c), std::end(c));
}

template <class C, class... Args>
auto join(C && c, Args &&... args)
{
    auto tmp = join(std::forward<Args>(args)...);
    return boost::join(std::forward<C>(c), tmp);
}

int main(int, const char*[])
{
    auto a = std::vector<int>{7, 8, 9};
    auto b = std::vector<int>{4, 5, 6};
    auto c = std::vector<int>{1, 2, 3};
    auto d = std::vector<int>{1, 2, 3};
    
    auto r2 = join(a, b, c, d);
    boost::sort(r2);
    
    print_vec(a);
    print_vec(b);
    print_vec(c);
    print_vec(d);
    print_vec(r2);

    return 0;
}
