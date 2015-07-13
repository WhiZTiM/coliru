#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// templated

template<typename Type>
struct T {
    T() = default;
    T(Type const&) {}
};

template<typename Type1, typename Type2>
T<Type1> operator*(T<Type1> lhs, T<Type2> const&) { return lhs; }

// non templated

struct R {
    R() = default;
    R(int const&) {}
};

R operator*(R lhs, R const&) { return lhs; }

int main() {
    auto x = R() * 1;
    auto y = T<int>() * 1;
}