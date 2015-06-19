#include <type_traits>

template<typename... T>
struct typelist {};

template<typename... L1, typename... L2>
auto operator+(typelist<L1...>, typelist<L2...>) { return typelist<L1..., L2...>{}; }

template<typename... Lists>
struct Join {
    using type = typename std::conditional<sizeof...(Lists), decltype((Lists{} + ...)), typelist<>>::type;
};

int main()
{
    static_assert(std::is_same< Join<>::type
                              , typelist<>
                              >::value, ":(");
}
