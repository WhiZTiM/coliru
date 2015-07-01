#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> values = {"first", "second", "last"};
    
    for(const auto value : values)
    {
        std::cout << value << "\n";
    }
}
