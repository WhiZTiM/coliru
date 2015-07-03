#include <iostream>

template <class ... Args>
void foo(Args&&... a) {
    ((std::cout << a << '\n'), ...);
}

template <class ... Args>
void print(Args&&... a) {
    (foo(a), ...);
}

int main() {
    print(1, 2, 3, 4, 5);
    print();
}