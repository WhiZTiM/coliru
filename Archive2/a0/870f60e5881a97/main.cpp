#include <vector>
#include <iostream>

template <std::size_t N>
constexpr std::size_t sum(char const (&str)[N]) {
    unsigned char sum = 0;
    for(char c : str)
        sum += c;
    return sum;
}

int main() {
    static_assert(sum("Hello, World !") == 137, "");
}