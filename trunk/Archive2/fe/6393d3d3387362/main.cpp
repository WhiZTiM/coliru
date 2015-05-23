#include <iostream>
#include <type_traits>
#include <tuple>

namespace detail {
    template <typename... Ts> struct tuple : std::tuple<Ts...> {
        using std::tuple<Ts...>::tuple;
    };
    template <typename T0> struct tuple<T0> : std::tuple<T0> {
        using std::tuple<T0>::tuple;
        T0&& _0 = std::get<0>(*this);
    };
    template <typename T0, typename T1> struct tuple<T0, T1> : std::tuple<T0, T1> {
        using std::tuple<T0, T1>::tuple;
        T0&& _0 = std::get<0>(*this);
        T1&& _1 = std::get<1>(*this);
    };
    template <typename T0, typename T1, typename T2> struct tuple<T0, T1, T2> : std::tuple<T0, T1, T2> {
        using std::tuple<T0, T1, T2>::tuple;
        T0&& _0 = std::get<0>(*this);
        T1&& _1 = std::get<1>(*this);
        T2&& _2 = std::get<2>(*this);
    };
    template <typename... Ts> constexpr tuple<Ts&&...> forward_as_tuple(Ts&&... vs) {
        return tuple<Ts&&...>{ std::forward<Ts>(vs)... };
    }
}

#define LR(EXPR) (auto&&... _ps) \
{ auto p = detail::forward_as_tuple(_ps...); return EXPR; }

int main()
{
    std::cout << []LR(p._0)("test");
    std::cout << []LR(p._0 + p._1)(2, 3); 
    std::cout << []LR(p._0 + p._1)(std::string("hello "), std::string(" world!"));
}
