#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string makeFineStr(const std::string & str)
{
    std::string tmp(str);
    size_t pos;
    while((pos = tmp.find(' ')) != tmp.npos)
    {
        tmp.erase(pos,1);
    }
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
