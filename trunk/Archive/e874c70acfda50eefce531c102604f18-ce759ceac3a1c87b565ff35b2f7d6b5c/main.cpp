#include <cstdint>
#include <limits>

#include <iostream>

int main() {
    auto x = std::numeric_limits<std::int32_t>::min();
    std::cout << -x;
}