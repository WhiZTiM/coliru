#include <iostream>
#include <string>
#include <vector>
#include <array>

constexpr bool any(std::initializer_list<bool> arr) { 
    for(auto var : arr) { if (var) return true; }
    return false;
}

int main()
{
    static_assert(any({false, false, true, false}), "");
}
