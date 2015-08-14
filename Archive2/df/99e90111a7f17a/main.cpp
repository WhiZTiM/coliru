#include <tuple>
#include <type_traits>
#include <iostream>

template <typename... Ts, typename... Us>
auto compare(const std::tuple<Ts...>& t1, const std::tuple<Us...>& t2)
    -> typename std::enable_if<sizeof...(Ts) == sizeof...(Us), bool>::type
{
    return t1 == t2;
}

template <typename... Ts, typename... Us>
auto compare(const std::tuple<Ts...>& t1, const std::tuple<Us...>& t2)
    -> typename std::enable_if<sizeof...(Ts) != sizeof...(Us), bool>::type
{
    return false;
}

int main()
{
    std::tuple<int, int> t1(1, 2);
    std::tuple<int> t2(1);
    
    std::cout << compare(t1, t2) << std::endl;
    std::cout << compare(t1, t1) << std::endl;
}
