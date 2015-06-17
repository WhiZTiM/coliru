#include <string>
#include <iostream>
 
int main()
{
    std::string a = "                  ";
 
    a = a.substr(0, a.find_last_not_of(" \t\n\v\f\r")+1);
    std::cout << a << " " << a.size() << '\n';
    
    if(a.size() > 0)
    {
        a = a.substr(a.find_first_not_of(" \t\n\v\f\r"));
        std::cout<< a << " " << a.size() << '\n';
    }
 
    /*std::string sub2 = a.substr(5, 3);
    std::cout << sub2 << '\n';
 
    std::string sub3 = a.substr(12, 100);
    std::cout << sub3 << '\n';
 
    std::string sub4 = a.substr(a.size()-3, 50);
    std::cout << sub4 << '\n';*/
}