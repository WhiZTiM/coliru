#include <unordered_map>
#include <string>
#include <iostream>


int main()
{
    std::unordered_map<int, std::string> m;
    m[1] = "First";
    m[2] = "Second";
    m[3] = "Third";
    
    for(const auto& pair: m)
    {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
    
    return 0;
}