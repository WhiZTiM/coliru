#include <vector>
#include <iostream>

template <std::size_t N>
constexpr unsigned char sum(char const (&str)[N]) {
    unsigned char sum = 0;
    for(char c : str)
        sum += c;
    return sum;
}

template <char C>
struct Char {
    static constexpr char const value = C;
};

int main() {
    static_assert(sum("Hello, World !") == 137, "");
    std::cout << Char<"Hello World !"[4]>::value << '\n';
}