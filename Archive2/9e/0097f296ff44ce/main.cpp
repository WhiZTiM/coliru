#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <regex>


int main()
{
    static std::regex re{"\\.(m|b)tf$"};
    std::string path{"/foo/bar/texture.mtf"};
    
    path = std::regex_replace(path, re, "");
    
    std::cout << path << '\n';
}
