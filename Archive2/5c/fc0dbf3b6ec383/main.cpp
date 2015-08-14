#include <type_traits>
#include <utility>

namespace detail
{
    template <typename T, std::size_t I, std::size_t J, typename... Ts>
    constexpr bool has_dupe = false;
    
    template <typename T, std::size_t I, std::size_t J, typename U, typename... Ts>
    constexpr bool has_dupe<T, I, J, U, Ts...> = has_dupe<T, I, J+1, Ts...>;
    
    template <typename T, std::size_t I, std::size_t J, typename... Ts>
    constexpr bool has_dupe<T, I, J, T, Ts...> = true;
    
    template <typename T, std::size_t I, typename... Ts>
    constexpr bool has_dupe<T, I, I, T, Ts...> = has_dupe<T, I, I+1, Ts...>;
    
    template <typename S, typename... Ts>
    constexpr bool no_dupes = false;
    
    template <typename... Ts, std::size_t... Is>
    constexpr bool no_dupes<std::index_sequence<Is...>, Ts...> = !(has_dupe<Ts, Is, 0, Ts...> || ...);
}

template <typename... Ts>
constexpr bool no_dupes = detail::no_dupes<std::index_sequence_for<Ts...>, Ts...>;

int main()
{
    static_assert(no_dupes<int, float, char, double>, "!");
    static_assert(!no_dupes<int, float, char, double, double>, "!");
}
