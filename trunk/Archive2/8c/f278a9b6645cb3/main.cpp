#include <iostream>

struct X_ {

template <typename A>
static const A& sum(const A& a) {
    return a;
}

template <typename A, typename B>
static auto sum(const A&a, const B& b) -> decltype(a + b) {
    return a + b;
}

template <typename A, typename B, typename... C>
static auto sum(const A& a, const B& b, const C&... c) -> decltype(a + b + sum(c...)) {
    return a + b + sum(c...);
}
};


int main() {
    std::cout << X_::sum(1, 1.5, 2) << '\n';
}
