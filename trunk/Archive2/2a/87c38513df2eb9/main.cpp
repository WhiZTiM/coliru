#include <tuple>
#include <utility>
#include <type_traits>

template <typename T, typename U>
struct selector;

template <typename T, std::size_t... Is>
struct selector<T, std::index_sequence<Is...>>
{
    using type = std::tuple<typename std::tuple_element<Is, T>::type...>;
};

template <std::size_t N, typename... Ts>
struct remove_last_n
{
    using Indices = std::make_index_sequence<sizeof...(Ts)-N>;  
    using type = typename selector<std::tuple<Ts...>, Indices>::type;
};

int main()
{
    using X = remove_last_n<2, int, char, bool, int>::type;
    static_assert(std::is_same<X, std::tuple<int, char>>::value, "types do not match");
}
