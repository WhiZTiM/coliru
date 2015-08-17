#include <type_traits>
#include <utility>

namespace detail
{
    template <typename T, std::size_t I, std::size_t J, typename... Ts>
    constexpr bool has_duplicate = false;
    
    template <typename T, std::size_t I, std::size_t J, typename U, typename... Ts>
    constexpr bool has_duplicate<T, I, J, U, Ts...> = has_duplicate<T, I, J+1, Ts...>;
    
    template <typename T, std::size_t I, std::size_t J, typename... Ts>
    constexpr bool has_duplicate<T, I, J, T, Ts...> = true;
    
    template <typename T, std::size_t I, typename... Ts>
    constexpr bool has_duplicate<T, I, I, T, Ts...> = has_duplicate<T, I, I+1, Ts...>;
    
    template <typename S, typename... Ts>
    constexpr bool has_no_duplicates = true;
    
    template <typename... Ts, std::size_t... Is>
    constexpr bool has_no_duplicates<std::index_sequence<Is...>, Ts...> = !(has_duplicate<Ts, Is, 0, Ts...> || ...);
}

template <typename... Ts>
constexpr bool has_no_duplicates = detail::has_no_duplicates<std::index_sequence_for<Ts...>, Ts...>;

int main()
{
    static_assert(has_no_duplicates<int, float, char, double>, "!");
    static_assert(!has_no_duplicates<int, float, char, double, double>, "!");
}
