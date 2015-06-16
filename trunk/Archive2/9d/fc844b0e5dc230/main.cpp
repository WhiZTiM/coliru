#include<iostream>
#include<sstream>
#include<string>

int main(int argc, char ** argv)
{
    int i;
    char *s = "12a3";
    std::string str(s);
    i = std::stoi(str);
    std::cout << i << std::endl;
}