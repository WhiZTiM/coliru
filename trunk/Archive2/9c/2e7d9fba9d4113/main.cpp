#include <iostream>
#include <string>
#include <vector>

void f(std::string s)
{
    std::cout << "s.data() " << (void*)s.data() << '\n';
}

std::string operator ""_s(const char* str, size_t len) { return std::string{str, len}; }

std::string s() { return "abcd"; }

int main()
{
    std::cout << (void*)("bar"_s.data()) << '\n';
    std::cout << (void*)("foo"_s.data()) << '\n';
    std::cout << (void*)("bar"_s.data()) << '\n';
    f("bar"_s);
    f("abc");
    f("xyz");
    f("abc");
}
