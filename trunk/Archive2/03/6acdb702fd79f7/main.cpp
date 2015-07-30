#include <iostream>
void foo(long) {
    std::cout << "int" << '\n';
}
void foo(short) {
    std::cout << "double" << '\n';
}

int main() {
    int i = 2;
    foo({i});
}