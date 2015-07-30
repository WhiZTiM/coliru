#include <iostream>
void foo(int) {
    std::cout << "int" << '\n';
}
void foo(double) {
    std::cout << "double" << '\n';
}

int main() {
    foo({2.1});
    foo(2.1);
}