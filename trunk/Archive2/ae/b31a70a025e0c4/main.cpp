#include <map>
#include <typeinfo>
#include <typeindex>

template <typename... T>
void foo() {
    std::map<std::type_index, size_t> m;
    auto dummy = {m.erase(typeid(T))...};
    (void)dummy;
}

int main() {
    foo<int, size_t, char>();
}