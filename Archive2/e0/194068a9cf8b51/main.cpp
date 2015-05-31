#include <iostream>

int main()
{
    int f = 15'999'999;
    std::cout<< (f%16'000'000) << std::endl;
    std::cout<< ((f + 16'000'000)%32'000'000) << std::endl;
    
    return 0;
}