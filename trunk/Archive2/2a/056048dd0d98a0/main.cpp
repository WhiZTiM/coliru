#include <iostream>
#include <sstream>

int main() {
    const std::string input = "0xDEAD";
    //const std::string input = "75";
    std::istringstream buf(input);
    long val;
    buf >> val;
    
    std::cout << "Result: " << val << std::endl;
}
