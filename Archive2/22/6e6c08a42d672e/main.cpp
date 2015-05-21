#include <string>
#include <tuple>
#include <iostream>

int main()
{
    using namespace std::literals::string_literals;
    auto s = "hello, world!\n"s;
    auto sɹoʇɐɹǝʇı = std::make_pair(s.rbegin(), s.rend());
    for(; sɹoʇɐɹǝʇı.first != sɹoʇɐɹǝʇı.second; ++sɹoʇɐɹǝʇı.first) std::cout << *sɹoʇɐɹǝʇı.first;
}
