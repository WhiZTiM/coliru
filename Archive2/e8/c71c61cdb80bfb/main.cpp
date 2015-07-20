#include <iostream>
#include <string>
#include <tuple>
#include <array>
#include <utility>
#include <type_traits>
#include <cstddef>
#include <boost/lexical_cast.hpp>

template <typename T>
struct converter;

template <std::size_t... Is>
struct converter<std::index_sequence<Is...>>
{
    std::tuple<decltype(void(Is), std::string{})...> t;
    
    converter(const std::array<std::string, sizeof...(Is)>& arr) : t(arr[Is]...) {}
    
    template <typename... Ts>
    operator std::tuple<Ts...>()
    {
        return std::tuple<Ts...>(boost::lexical_cast<typename std::decay<Ts>::type>(std::get<Is>(t))...);
    }
};

template <std::size_t N>
converter<std::make_index_sequence<N>> Convert(const std::array<std::string, N>& arr)
{
    return {arr};
}

int main()
{
    std::array<std::string, 2> arr{ "1", "2.0" };
    
    std::tuple<int, double> t = Convert(arr);
    
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    
    std::tuple<int, float, double, char, short> b = Convert<5>({"1", "2", "3", "4", "5"});
    
    std::cout << std::get<0>(b) << std::endl;
}
