#include <map>
#include <iostream>
#include <tuple>


template <typename T1, typename T2>
struct OrderIndependentPair
{
  T1 first;
  T2 second;

  bool operator<(const OrderIndependentPair &rhs) const
  {
    if (rhs.first< rhs.second)
    {
        return std::tie(first, second) < std::tie(rhs.first, rhs.second);
    }
    else
    {
        return std::tie(first, second) < std::tie(rhs.second, rhs.first);
    }
  }
};

int main()
{
    using Pair = OrderIndependentPair<std::string, std::string>;

    using Map = std::map<Pair,int>;

    Map m;
    Pair p1{"foo", "bar"};
    m[p1] = 42;
        
    Pair p2{"bar", "foo"};
    std::cout << m[p1] << std::endl;
    std::cout << m[p2] << std::endl;
    return 0;
}