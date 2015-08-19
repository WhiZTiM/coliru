#include <string>
#include <iostream>
#include <sstream>

template <typename T>
std::string toString(const T& a)
{
    std::ostringstream ss;
    ss << a;
    return ss.str();
}

int main()
{
    char s[100] = "I am a string with spaces";
    std::cout << toString(s);
} 
