#include <iostream>

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
 
int main()
{
    color col = red;
    std::cout << "col = " << col << '\n';
}