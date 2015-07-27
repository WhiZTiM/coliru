#include <iostream>
#include <sstream>

int main() {
    std::cout << std::boolalpha << bool(std::ostringstream().flags() & std::ios_base::dec);   
}