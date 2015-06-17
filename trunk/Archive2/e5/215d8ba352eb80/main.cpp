#include <sstream>
#include <iostream>

int main() {
    std::stringstream ssb("Setting string", std::ios_base::out | std::ios_base::ate);
    std::cout << ssb.str() << std::endl;
    ssb << " adding to string";
    std::cout << ssb.str() << std::endl;
}