#include <iostream>
void foo(long) {
    std::cout << "int" << '\n';
}
void foo(short) {
    std::cout << "double" << '\n';
}

int main() {
    foo({2.1});
}