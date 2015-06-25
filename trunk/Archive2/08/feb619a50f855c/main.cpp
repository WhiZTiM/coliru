#include<stdio.h>
#include <iostream>

class enString : public std::string
{
public:
    enString() : std::string("") {};
    enString(char* str) : std::string(str) {};
    enString(const char* str) : std::string(str) {};
    inline operator const char*() const { return c_str(); }
};

int main()
{
    enString mystr("Gigel");
    std::cout << mystr << '\n';
    
    std::printf("%s\n", mystr);
}
