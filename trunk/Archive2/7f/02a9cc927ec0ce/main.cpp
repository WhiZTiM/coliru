#include <string>
#include <tuple>
#include <iostream>

int main()
{
    using namespace std::literals::string_literals;
    auto s = "hello, world!\n"s;
    auto sɹoʇɐɹǝʇı = std::make_pair(s.begin(), s.end());
    for(; sɹoʇɐɹǝʇı.first != sɹoʇɐɹǝʇı.second; ++sɹoʇɐɹǝʇı.first) std::cout << *sɹoʇɐɹǝʇı.first;
}
