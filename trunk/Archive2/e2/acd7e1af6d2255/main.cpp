#include <vector>

struct A {
    struct B;
    std::vector<B> v;
    A() {};
};

// A::B still incomplete
A a;

struct A::B{};

int main() {
}
