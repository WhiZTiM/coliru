#include <iostream>
#include <string>
#include <vector>

std::string& retStr()
{
    std::string str;
    std::cin >> str;
    return str;
}

int main()
{
    std::cout << retStr() << std::endl;
}
