#include <locale>
#include <string>
#include <iostream>


int main(int argc, char* argv[])
{
    std::string unescaped = R"ololo({"json":"here"})ololo";
    std::cerr << unescaped << std::endl;

}