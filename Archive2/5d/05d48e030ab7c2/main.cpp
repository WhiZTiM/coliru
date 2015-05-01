#include <iostream>
int main() {
    int x = 1;
    int y = 2;
    (x > y ? x : y) = 100;
    std::cout << (x > y ? x : y) << '\n';
}
