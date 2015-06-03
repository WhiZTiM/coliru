#include <iostream>
#include <string>
#include <memory>
#include <vector>

template<typename T>
struct Polynomial {};

template<typename T>
Polynomial<T> operator*(Polynomial<T> lhs, Polynomial<T> rhs) { return lhs; }

template<typename T>
Polynomial<T> operator+(Polynomial<T> lhs, Polynomial<T> rhs) { return lhs; }

int main() {
    auto p = std::make_unique<Polynomial<int>>();
    auto q = std::make_unique<Polynomial<int>>();
    auto x = (*p) * (*q);
    auto y = (*q) + (*p);
}