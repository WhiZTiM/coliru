#include <iostream>

int richa(int n, int x, int y) {
    if (n <=0 || x <= 0 || y <= 0) return 0;
    if (n + 1 < x + y) return 0;
    if (n == 1 && x == 1 && y == 1) return 1;
    return (n-2)*richa(n-1, x, y) + richa(n-1, x-1, y) + richa(n-1, x, y-1);
}

int main() {
    std::cout << richa(1, 1, 1) << std::endl;
    std::cout << richa(5, 1, 2) << std::endl;
}
