#include <iostream>
#include <string>
#include <ctime>
#include <bitset>

int main()
{
    time_t a;
    struct tm *timeInfo;
    time(&a);
    timeInfo = localtime(&a);
    const char* time = asctime(timeInfo);
    std::cout << "time is " << time << "time_t size: " << sizeof(time_t) << " long int size: " << sizeof(long int) << std::endl << std::endl;
    
    std::bitset<32> poop;
    std::bitset<32> lol;
    char* az;
    az = new char[3]();
    az[1] |= 0b1; 
    poop[0] = 1;
    poop[3] = 1;
    lol[0] = 1;
    lol[1] = 1;
    lol[4] = 1;
    poop &= lol;
    std::cout << poop << " " << sizeof(int)*8  << "  az char:" ;
    for(size_t i = 0; i < 3*8; ++i)
        std::cout << static_cast<int>(az[i/8]);
    
}
