#include <iostream>
#include <utility>
#include <tuple>
#include <cstddef>

template <typename... Ts> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

template <typename...> struct typelist {};
template <typename T> struct identity { using type = T; };

template <class... Ts, class... Us>
auto Method3(typelist<Ts...>, typelist<Us...>, const typename identity<Us>::type&... parameters)
    -> std::tuple<Ts...>
{
    TD<Ts...>();
    TD<Us...>();
    return {};
}

template <class... Ts, class... Params, std::size_t... Is>
auto Method2(std::index_sequence<Is...>, Params&&... parameters)
    -> decltype(auto)
{
    return Method3(typelist<typename std::tuple_element<Is, std::tuple<Ts...>>::type...>{}
                 , typelist<typename std::tuple_element<Is + sizeof...(Is), std::tuple<Ts...>>::type...>{}
                 , std::forward<Params>(parameters)...);
}

template <class... Ts, class... Params>
auto Method(Params&&... parameters)
    -> decltype(auto)
{
    return Method2<Ts...>(std::make_index_sequence<sizeof...(Ts)/2>{}, std::forward<Params>(parameters)...);
}

int main()
{
    std::tuple<int, short, float> R = Method<int, short, float, double, bool, char>(3.14, true, 'a');
    
    (void)R;
}
