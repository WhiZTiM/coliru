
#include <vector>
#include <string>
#include <iostream>

int main ( void )
{
    std::vector<std::string> sv;
    sv.push_back("Sample string");
    sv.push_back("Another piece of text");
    
    for(auto& s : sv)
    {
        for(const auto& c : s)
        {
            std::cout<<c<<", ";
        }
        
        std::cout<<"\n";
    }
    
    return 0;
}