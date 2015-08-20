#include <type_traits>

struct A{};

template <typename T>
void foo(T&&){}

template <typename T>
std::enable_if_t<std::is_same<std::decay_t<T>,A>::value> foo(T){}

int main()
{
    foo(0);
    foo(A{});
}