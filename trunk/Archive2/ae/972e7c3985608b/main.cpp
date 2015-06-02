#include <iostream>
#include <bitset>
using namespace std;


int main() {
   
    std::bitset<6> bs('Z'); // change to any char 
    std::cout << bs.to_string() << "\n";
    std::cout << static_cast<char>(std::stoi(bs.to_string(),0,2) + 64);
    return 0;
}