#include <cstdio>
class C {
    friend void hello() { std::puts("Hello, world!"); }
};
int main() {
    hello();
}