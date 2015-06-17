#include <sstream>
#include <iostream>

int main() {
    std::ostringstream ssb("Setting string", std::ios_base::ate);
    std::cout << ssb.str() << std::endl;
    ssb << " adding to string";
    std::cout << ssb.str() << std::endl;
}