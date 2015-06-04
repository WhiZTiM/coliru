#include <string>
#include <algorithm>
#include <iostream>

int main()
{
    using namespace std::literals::string_literals;
    auto s = "ATTENTION ́ECOLE"s;
    auto const from = s.begin();
    auto const to = s.end();
    auto const pos = std::find(from, to, '\x81');
    std::cout << "Prefix:\n";
    std::cout << std::string { from, pos } << '\n';
    std::cout << "Suffix:\n";
    std::cout << std::string { pos, to } << '\n';
}