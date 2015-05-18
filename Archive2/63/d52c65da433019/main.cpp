#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha << std::is_pointer<decltype("sss")>::value;
    std::cout << std::boolalpha << std::is_array<decltype("sss")>::value;
}