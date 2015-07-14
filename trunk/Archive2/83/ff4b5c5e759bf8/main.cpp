#include <iostream>
#include <string>
#include <vector>

bool isMirror(const std::string & first, const std::string & second)
{
    if (first.size() != second.size()) return false;
    
    std::string tmp(first);
    tmp.append(first);
    if (tmp.find(second) != first.npos) 
    {
        return true;
    }
    return false;
}

int main()
{
    std::string s1 = "CABC";
    std::string s2 = "CCAB";
    std::cout<<isMirror(s1,s2);
}
