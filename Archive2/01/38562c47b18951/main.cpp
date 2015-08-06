#include <iostream>
#include <string>
#include <locale>
#include <sstream>

bool convert(const std::string & text)
{
    std::istringstream iss(text);
    iss.imbue(std::locale::classic());
    double result;
    iss >> result;
    if (iss.eof())
        return true;
    else
        return false;
}

int main()
{
    std::cout << convert("123.456") << std::endl;
    std::cout << convert("123.456abc") << std::endl;
    std::cout << convert("123.456e5") << std::endl;
    std::cout << convert("e5") << std::endl;
    return 0;
}