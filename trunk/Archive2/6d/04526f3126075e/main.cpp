#include <iostream>
#include <string>

// color may be red (value 0), yellow (value 1), green (value 20), or blue (value 21)
enum color {
    red,
    yellow,
    green = 20,
    blue
};
    
//enumeration types (both scoped and unscoped) can have overloaded operators
std::ostream& operator<<(std::ostream& os, color c)
{
    switch(c) {
         case red    : os << "red";    break;
         case yellow : os << "yellow"; break;
         case green  : os << "green";  break;
         case blue   : os << "blue";   break;
         default : os.setstate(std::ios_base::failbit);
    }
    return os;
}

std::string str(color c)
{
    std::string s;
    switch(c) {
         case red    : s = "red";    break;
         case yellow : s = "yellow"; break;
         case green  : s = "green";  break;
         case blue   : s = "blue";   break;
         default : s = "not a fucking color";
    }
    return s;
}
 
int main()
{
    color col = red;
    std::cout << "col = " << col << '\n';
    std::cout << "str(col) = " << str(col) << '\n';
}