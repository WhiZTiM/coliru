#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>

std::string makeFineStr(const std::string & str)
{
    std::string tmp(str);    
    std::remove_if(tmp.begin(), tmp.end(), [](char x) { return std::isspace(x);});
    std::reverse(tmp.begin(), tmp.end());
    return tmp; // RVO makes fine....
}

int main()
{
   std::string myStr = "Hello World! =)";
   std::cout<<myStr<<std::endl;
   std::string changedStr = makeFineStr(myStr);
   std::cout<<changedStr;
}
