#include <iostream>

int main() {
    std::uint32_t i;
    std::cin >> std::hex >> i;
    if(!std::cin)
        std::cout << "Invalid hex\n";
    else
        std::cout << "i = " << i << '\n';
}
