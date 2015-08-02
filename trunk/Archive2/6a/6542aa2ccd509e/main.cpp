#include <cstdint>
#include <type_traits>

template <bool...> struct bool_pack;
template <bool... v>
using all_true = std::is_same<bool_pack<true, v...>, bool_pack<v..., true>>;

template <class... Args>
std::enable_if_t<all_true<std::is_convertible<Args, std::size_t>{}...>{}> check(Args... args) {}


int main() {
    check(1, 1.0f, 'a');
    //check(1, 1.0f, "a"); // Uncomment to see it fail cleanly
}