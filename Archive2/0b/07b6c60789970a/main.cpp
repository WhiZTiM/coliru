#include <iostream>
#include <type_traits>
#include <tuple>

namespace detail {
    template <typename... Ts> struct tuple : std::tuple<Ts...> {
        using std::tuple<Ts...>::tuple;
        template <typename T> constexpr auto operator[](T)
        -> std::tuple_element_t<T::value, std::tuple<Ts...>>
        { return std::get<T::value>(*this); }
    };
    template <typename... Ts> constexpr tuple<Ts&&...> forward_as_tuple(Ts&&... vs) {
        return tuple<Ts&&...>{ std::forward<Ts>(vs)... };
    }
    namespace placeholders {
        constexpr std::integral_constant<size_t, 0> _0;
        constexpr std::integral_constant<size_t, 1> _1;
        constexpr std::integral_constant<size_t, 2> _2;
        constexpr std::integral_constant<size_t, 3> _3;
        constexpr std::integral_constant<size_t, 4> _4;
        constexpr std::integral_constant<size_t, 5> _5;
        constexpr std::integral_constant<size_t, 6> _6;
        constexpr std::integral_constant<size_t, 7> _7;
        constexpr std::integral_constant<size_t, 8> _8;
        constexpr std::integral_constant<size_t, 9> _9;
    }
}

#define LR(EXPR) (auto&&... _ps) \
{ using namespace detail::placeholders; auto p = detail::forward_as_tuple(_ps...); return EXPR; }

int main()
{
    std::cout << []LR(p[_0])("test");
    std::cout << []LR(p[_0] + p[_1])(2, 3); 
    std::cout << []LR(p[_0] + p[_1])(std::string("hello "), std::string(" world!"));
}
