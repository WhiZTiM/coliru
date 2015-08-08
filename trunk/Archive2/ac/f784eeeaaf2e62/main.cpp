#include <tuple>
#include <utility>

// from http://stackoverflow.com/a/19759105/678093
template <typename T, std::size_t... Is>
struct selector
{
    using type = std::tuple<typename std::tuple_element<Is, T>::type...>;
};

template <std::size_t N, typename... Ts>
struct remove_last_n
{
    using Indices = std::make_index_sequence<sizeof...(Ts)-N>;  
    using type = selector<std::tuple<Ts...>, Indices>, 
    
};
