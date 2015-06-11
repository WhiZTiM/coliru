#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist{1, 100};
    
    const auto a = dist(rd);
    
    size_t alen = a > 10 ? 2 : 1;
    size_t asum = a/10 + a%10;
    
    std::cout << "a: " << a <<
        "\nLen: " << alen <<
        "\nSumm: " << asum << std::endl;
}
