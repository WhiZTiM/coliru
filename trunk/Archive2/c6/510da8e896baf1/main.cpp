#include <iostream>

template<unsigned X = 0, typename T>
void f(T&&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }

int main() {
    f(20);
    f<20>(10);
}