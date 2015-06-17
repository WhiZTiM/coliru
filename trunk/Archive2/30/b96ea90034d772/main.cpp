#include <iostream>
#include <sstream>
#include <locale>
 
int main()
{
    std::istringstream iss;
    iss.imbue(std::locale("en_US.UTF8"));
 
    std::cout << "Current locale      : " << iss.getloc().name().c_str()          << '\n';
    std::cout << "Current locale (buf): " << iss.rdbuf()->getloc().name().c_str() << '\n';
 
    std::istream wrap(iss.rdbuf());
    wrap.imbue(std::locale());
    std::cout << "Global locale       : " << iss.getloc().name().c_str()          << '\n';
    std::cout << "Global locale (buf) : " << iss.rdbuf()->getloc().name().c_str() << '\n';
}
