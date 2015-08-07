#include <type_traits>

void foo();

int main() {
    static_assert(std::is_same<decltype(foo), void()>{});
    static_assert(std::is_same<decltype(foo), void(*)()>{});
}