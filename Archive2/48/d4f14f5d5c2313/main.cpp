#include <map>

template <typename... T>
void foo() {
    std::map<size_t, size_t> m;
    auto dummy = {m.erase(sizeof(T))...};
    (void)dummy;
}

int main() {
    foo<int, size_t, char>();
}