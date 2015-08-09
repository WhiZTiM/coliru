#include <string>
#include <cassert>
#include <iostream>

int main() {
    using namespace std::string_literals;
    assert(u8"\xF4"s != u8"\u00F4"s);
    assert(u8"\xF4"s.size() == 1);
    assert(static_cast<unsigned char>(u8"\xF4"[0]) == 0xF4);
    std::cout << "Success\n";
}
