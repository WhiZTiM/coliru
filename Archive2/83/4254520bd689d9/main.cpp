#include <type_traits>
#include <utility>

namespace detail {
struct has_hello {
    template<typename T, typename X = decltype(std::declval<T>().hello("world"))>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};
} // detail

template<typename T>
struct has_hello : decltype(detail::has_hello::test<T>(0)) {};

struct lol {
    void hello(const char*) {}
};

struct nope {};

int main() {
    static_assert(has_hello<lol>::value, "pass");
    static_assert(has_hello<nope>::value, "fail");
}