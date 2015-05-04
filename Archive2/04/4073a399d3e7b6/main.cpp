#include <iostream>

int main(int argc, char** argv) {
    int input = 0;
    float input2 = 0;
    //Since this is a float, this can also be written as 0.0f.
    
    std::cin >> input >> input2;
    //Note how we use std::cin to write to two variables.
    //They must be separated by whitespace, and no other character.
    
    std::cout << "Input 1: " << input << std::endl;
    std::cout << "Input 2: " << input2 << std::endl;
    return 0;
}