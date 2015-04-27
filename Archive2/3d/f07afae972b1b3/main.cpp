#include <iostream>
#include <string>
#include <map>

int main()
{
    std::map<char[3], int> toto;
    char tutu[3]  = "to";
    toto[tutu] = 4;
}
