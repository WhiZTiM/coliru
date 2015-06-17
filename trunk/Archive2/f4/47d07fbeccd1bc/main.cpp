#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    std::vector<unsigned char>
        charSet{0x80, 0x80, 0x80, 0x80, 0x80, 0x00};
    unsigned char
        charHead = 0x40;
    for(unsigned int i = 5; i--> 0;){
        charHead = (charHead >> 1) | 0x80;
        std::cout << charHead << charSet.data() << "\n";
    }
    return 0;
}
