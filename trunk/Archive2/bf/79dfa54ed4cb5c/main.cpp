#include <iostream>
#include <locale>
#include <sstream>
using namespace std;

struct space_out : std::numpunct<char> {
    char do_thousands_sep()   const { return ' '; }  // separate with spaces
    std::string do_grouping() const { return "\1"; } // groups of 1 digit
};
 
int main()
{
    cout << "default locale: " << 12345678 << '\n';
    cout.imbue(std::locale(std::cout.getloc(), new space_out));
    
    ostringstream oss;
    oss << "locale with modified numpunct: " << 12345678 << '\n';
    cout << oss.str() << endl;
    
    oss.imbue(std::locale());
    oss << "locale with modified numpunct: " << 12345678 << '\n';
    cout << oss.str() << endl;
}