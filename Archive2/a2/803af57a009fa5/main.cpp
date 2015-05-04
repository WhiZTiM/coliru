#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string argument;
    
    std::cout << "Please input a sentence (ending with a '.')\n";
    std::getline(std::cin, argument);
    
    std::cout << argument << '\n';
}