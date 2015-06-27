#include <iostream>

int main() {
    int x = 1;
    {
        int x = x ^ x;
        std::cout << x;
    }
}