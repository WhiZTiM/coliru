#include <iostream>
#include <random>
#include <string>

int main() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist{1, 100};
    
    auto a = dist(rd);
    auto as = std::to_string(a);
    std::cout << "a: " << a <<
        "\nLen: " << as.size() <<
        "\nSumm: " << std::accumulate(as.cbegin(), as.cend(), -as.size() * '0') << std::endl;
}
