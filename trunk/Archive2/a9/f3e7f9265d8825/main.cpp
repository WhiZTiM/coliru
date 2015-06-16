#include<iostream>
#include<sstream>
#include<string>

int main(int argc, char ** argv)
{
    int i;
    char *str = "12a3";
    std::stringstream ss;
    ss << str;
    if(!ss >> i){
        std::cout << "Conversion failed" << std::endl;
    } else {
        std::cout << i << std::endl;
    }
}