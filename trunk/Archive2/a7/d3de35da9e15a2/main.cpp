#include <iostream>
#include <string>
#include <vector>

struct Beer
{
    Beer(const char* s) : name(s) {}
    
    std::string name;
};

int main()
{
    std::vector<Beer> vec{ "Thier", "Bergmann", "Kronen" };
    
    for (std::vector<Beer>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << it->name << "-Pils\n";
    }
}