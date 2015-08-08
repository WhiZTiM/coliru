#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <type_traits>

template <typename F, typename C>
auto functional_map(F func, const C& v)
    -> std::vector<typename std::decay<decltype(func(*begin(v)))>::type>
{
    using B = typename std::decay<decltype(func(*begin(v)))>::type;
    std::vector<B> result;
    for (const auto& val : v) result.emplace_back(func(val));
    return result;
}

int square (int x)
{
    return x*x;
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::map<std::string, int> m = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
                                    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
    for (const auto& y : functional_map(square, v)) {
        std::cout << y / 2 << " ";
    }
    std::cout << '\n';
    auto square2 = [](double d){return d*d;};
    for (const auto& y : functional_map(square2, s)) {
        std::cout << y / 2 << " ";
    }
    std::cout << '\n';
    for (const auto& y : functional_map([](const std::pair<const std::string, int>& pr){
                                           return std::make_pair(pr.first, pr.second*pr.second);},
                                        m)) {
        std::cout << y.first << ": " << y.second << "; ";
    }
    std::cout << '\n';
    return 0;
}
