#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

int main()
{
    std::istringstream iss(
        "8C B6 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36"
        "83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68"
        "36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83"
        "68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36"
        "83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68"
        "36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83"
        "68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36"
        "83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68 36 83 68"
        "36 83 68 36 83 68 36 83 68 36 83 60 36");
        
    std::string byte;
    while(iss >> byte) {
        std::bitset<8> bits(std::stoul(byte, 0, 16));
        
        std::cout << bits << std::endl;
    }
}
