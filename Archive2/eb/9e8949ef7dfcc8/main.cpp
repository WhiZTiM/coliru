#include <iostream>
#include <string>
 
int main() 
{
    int i = 324;
    long l = 2309582;
    long long ll = 912348734;
    unsigned u = 2390;
    unsigned long ul = 98374982;
    unsigned long long ull = 89127498734;
    float f = 23.3253;
    double d = 23.43;
    long double ld = 323.232;
    
    std::cout << std::to_string(i) << std::endl;
    std::cout << std::to_string(l) << std::endl;
    std::cout << std::to_string(ll) << std::endl;
    std::cout << std::to_string(u) << std::endl;
    std::cout << std::to_string(ul) << std::endl;
    std::cout << std::to_string(ull) << std::endl;
    std::cout << std::to_string(d) << std::endl;
    std::cout << std::to_string(ld) << std::endl;
    std::cout << std::to_string(f) << std::endl;
    
    std::cout << std::to_string(0772734) << std::endl;
    std::cout << std::to_string(0x7734) << std::endl;
}