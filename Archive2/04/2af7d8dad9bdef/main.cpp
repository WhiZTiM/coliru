#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
    
int main()
{
   random_device rdGenerator;
    default_random_engine rndEngine;
    uniform_int_distribution<int> dstUniform(10,20);
for(int r = 0; r < 15; r++)
{cout << dstUniform(rndEngine)<<" ";}
    
    std::vector<std::string> words = {
       // "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << " " << std::endl;
}
