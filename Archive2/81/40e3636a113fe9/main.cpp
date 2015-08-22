#include <initializer_list>

struct A {
    A(std::initializer_list<char>);
    A(int, int);
};

int main() {
    int a = 4242;
    A{a, a};
}