#include <cstdio>

#define BARK printf("%s\n", __func__)

template <typename T> class A {
    using x = typename T::x;
};

template <typename T> void foo (T) { BARK; }

template <typename T> void foo (A<T>) { BARK; }

template <>
void foo<int> (int) { BARK; }

int main() { foo (5); }
