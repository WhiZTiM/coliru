#include <type_traits>

template<typename T>
struct foo {
    T bar();
};

template<typename T>
T foo<T>::bar() {
    return T{};
}

int main() {
    foo<int> f;
    f.bar();
}
