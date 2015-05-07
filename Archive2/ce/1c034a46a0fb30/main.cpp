#include <stddef.h>

template<size_t N = sizeof(void*)> struct a;

template<> struct a<4> {
    enum { b };
};

template<> struct a<8> {
    template<int> struct b {};
};

enum { c, d };

int main() {
    a<>::b<c>d;
    d;
}