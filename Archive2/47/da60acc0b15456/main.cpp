#include <iostream>

int main(int argc, char** argv) {
    char c;
    
    //While there are still character to get from std::cin
    while (std::cin.get(c))
    {
        //If the character 'c' is a digit or a period, print it out
        //An input "3.PIE14,)(^%PUMPKIN15" would end up printing 3.1415
        if (c >= '0' && c <= '9' || c == '.') {
            std::cout << c;   
        }
    }
    return 0;
}