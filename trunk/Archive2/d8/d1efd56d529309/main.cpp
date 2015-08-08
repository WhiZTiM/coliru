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
    using type = typename selector<std::tuple<Ts...>, Indices>::type; // fails
};

int main()
{
    using X = remove_last_n<2, int, char, bool, int>::type;
    static_assert(std::is_same<X, std::tuple<int, char>>::value, "types do not match");
}
