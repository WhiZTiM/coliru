#include <iostream>
#include <future>

int main() {
    int i = 10;
    while(--i) {}
    std::cout << i;
}