#include <map>
#include <iostream>
#include <utility>

template <typename Pair>
struct OrderIndependentPairComparison
{
    bool operator()(const Pair& lhs, const Pair& rhs) const
    {
        if (rhs.first < rhs.second)
        {
            return lhs < rhs;
        }
        else
        {
            return lhs < std::make_pair(rhs.second, rhs.first);
        }
    }
};

int main()
{
    using Pair = std::pair<std::string, std::string>;
    using Map = std::map<Pair,int, OrderIndependentPairComparison<Pair>>;

    Map m;
    Pair p1{"foo", "bar"};        
    Pair p2{"bar", "foo"};
    m[p1] = 42;
    std::cout << m[p1] << std::endl;
    std::cout << m[p2] << std::endl;
    return 0;
}