#include <iostream>

int main() {
    std::cout << "First message" << std::endl;
    
    std::cout.setstate(std::ios_base::failbit);
    std::cout << "Second message" << std::endl;
    
    std::cout.clear();
    std::cout << "Last message" << std::endl;
    
    return 0;
}
