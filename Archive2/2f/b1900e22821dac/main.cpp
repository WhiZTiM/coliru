#include <iostream>
#include <array>

template <typename T>
constexpr T e = T(2.71828);

template <typename T>
T EFoo(T phone, T home) {
    return e<T> * phone * home;
}

int main() {
    EFoo<float>(0.1, 0.2);
}