#include <array>
#include <iostream>

int main() {
    std::int16_t x = static_cast<std::int16_t>(std::int8_t(123)) + static_cast<std::int16_t>(std::int8_t(203));
    std::cout << x << '\n';
}