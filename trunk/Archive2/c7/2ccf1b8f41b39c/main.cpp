#include <iostream>
#include <string>
#include <ctime>
#include <bitset>
#include <vector>

int main()
{
    time_t a;
    struct tm *timeInfo;
    time(&a);
    timeInfo = localtime(&a);
    const char* time = asctime(timeInfo);
    std::cout << "time is " << time << "time_t size: " << sizeof(time_t) << " long int size: " << sizeof(long int) << std::endl << std::endl;
    bool boolean = true;
    std::bitset<32> poop;
    std::bitset<32> lol;
    std::vector<int> bis = {1,2,3};
    std::vector<int> xz(5);
    
    char* az;

    poop[0] = 1;
    poop[3] = 1;
    lol[0] = 1;
    lol[1] = 1;
    lol[4] = 1;
    az = new char[3]();
    *az |= 0x000003; 
    std::cout << static_cast<int>(*az)<< std::endl;
    *az <<= 3; 
    std::cout << static_cast<int>(*az)<< std::endl;
    int z;
    z = static_cast<int>(boolean);
    z <<= 1;
    
    int* bb = bis.data();
    std::copy(bb, bb+3, xz.begin());
    
    
    poop &= lol;
    std::cout<< bb+3 << "poop:" << poop << " " << z << " " << sizeof(int)*8 << std::endl;
    for(int i=0; i < xz.size(); ++i)
        std::cout << xz[i]<< std::endl;
    
}
