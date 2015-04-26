#include <cstddef>

struct A {
    static constexpr std::size_t f() { return 4; }
};

template<std::size_t N>
struct B : A {
    alignas(f()) char a[N];
};

int main(int argc, char** argv) {
    B b;
    return 0;
}