#include <string>
#include <cstring>
#include <iostream>

int main(int argc, char *argv[])
{
    std::string foo("hello", 5);
    std::cout << std::strlen(foo.c_str()) << std::endl;
}