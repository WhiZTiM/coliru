#include <type_traits>
#include <utility>
#include <cstddef>

template <typename T, template <T...> class Pack, T Value, size_t... indices>
auto FillHelper(std::index_sequence<indices...>) -> Pack<(indices, Value)...>;

template <typename T, template <T...> class P, int Size, T Value>
using Fill = decltype(FillHelper<T, P, Value>(std::make_index_sequence<Size>()));

template <int...> struct Pack;

int main() {
    using T = Fill<int, Pack, 10, 4>;
    static_assert(std::is_same<T, Pack<4, 4, 4, 4, 4, 4, 4, 4, 4, 4>>::value, "lol");
}