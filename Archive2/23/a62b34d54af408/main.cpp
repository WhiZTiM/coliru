#include<iostream>
#include<sstream>
#include<string>

int main(int argc, char ** argv)
{
    int i;
    char *str = "12a3";
    std::stringstream ss;
    ss << str;
    std::cout << !(ss >> i) << std::endl;
}