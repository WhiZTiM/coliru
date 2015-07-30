#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::string s = "/abcd\\sdf/sdf\\\\sd";
    std::cout<<s<<std::endl;
    std::string s2= boost::algorithm::replace_all_copy(s,"\\","/");
    std::cout<<s2<<std::endl;
    
    
    std::string sTmp(s);
    std::string pathSep = "\\";
	while(sTmp.find(pathSep) != std::string::npos)
	    sTmp.replace(sTmp.find(pathSep),pathSep.length(),"/");
    std::cout<<sTmp<<std::endl;
}
