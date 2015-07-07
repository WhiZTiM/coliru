#include <iostream>

int main() {
    bool a = true;
    bool b = false;
    
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    
    std::cout << "a: " << std::boolalpha << a << std::endl;
    std::cout << "b: " << std::boolalpha << b << std::endl;
    
} 