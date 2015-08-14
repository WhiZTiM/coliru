#include <type_traits>

template <typename...>
struct voider { using type = void; };

template <typename... Ts>
using void_t = typename voider<Ts...>::type;

template <typename T> 
struct type { };

template <typename... Ts>
struct dup_helper : type<Ts>... { };

template <typename, typename...>
struct is_valid : std::false_type { };

template <typename... Ts>
struct is_valid<void_t<dup_helper<Ts...>>, Ts...> : std::true_type { };
    
template <typename... Ts>
using has_no_duplicates = is_valid<void, Ts...>;

int main()
{
    static_assert(has_no_duplicates<int, float>{}, "");
    static_assert(!has_no_duplicates<float, float>{}, "");
}
