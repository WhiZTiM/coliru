#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

int main (int, char**) {
    std::cout << std::is_same<int, long>::value << std::endl;
    return 0;
}
