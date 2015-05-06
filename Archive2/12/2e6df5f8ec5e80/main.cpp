#include <bitset>
#include <iostream>
 
int main() 
{
    // empty constructor
    std::bitset<8> b1; // [0,0,0,0,0,0,0,0]
    b1[0] = true;
    for (int i = 1; i < 8; ++i) {
        b1[i] = !b1[i - 1];
    }
    std::cout << b1 << '\n';
}