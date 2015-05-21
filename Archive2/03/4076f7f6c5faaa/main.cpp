#include <string>
#include <tuple>
#include <iostream>

int main()
{
    using namespace std::literals::string_literals;
    auto s = "hello, world!"s;
    auto ‫iterators‬ = std::make_pair(s.rbegin(), s.rend());
    for(; ‫iterators‬.first != ‫iterators‬.second; ++‫iterators‬.first) std::cout << *‫iterators‬.first;
}