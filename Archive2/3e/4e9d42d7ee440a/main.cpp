#include <cstddef>

      constexpr std::size_t f() { return 4; }
const constexpr std::size_t g() { return 4; }

template<bool=true>
struct A {
    alignas(f()) int i;
    alignas(g()) int j;
};

int main(int argc, char** argv) {
    A<> a;
    return 0;
}