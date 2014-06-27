#include <iostream>
#include <utility>
#include <tuple>

template <typename Func, typename Tuple, std::size_t... Indices>
auto forward_to_function(Func&& f, Tuple&& t, std::index_sequence<Indices...>) {
    return f(std::get<Indices>(std::forward<Tuple>(t))...);
}

template <typename Func, typename Tuple>
auto forward_to_function(Func&& f, Tuple&& t) {
    constexpr auto n = std::tuple_size<std::remove_reference_t<Tuple>>::value;
    return forward_to_function(std::forward<Func>(f),
           std::forward<Tuple>(t),
           std::make_index_sequence<n>{});
}

int main() {
    auto Values = std::make_tuple(4, 8);
    auto Add = [] (int a, int b) -> int { return a + b; };

    auto Result = forward_to_function(Add, Values);

    std::cout << "Result: " << Result << std::endl;
}