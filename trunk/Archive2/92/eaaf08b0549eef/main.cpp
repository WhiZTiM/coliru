#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

map<string, string> groups = {
  {"EN", "\3"},  
  {"IN", "\3\2"}
  // etc
};

struct digit_separator : std::numpunct<char> 
{
    digit_separator(string g)
        : group(move(g))
    {
        
    }
    
    char do_thousands_sep()   const 
    { 
        return ','; 
    } 
    
    std::string do_grouping() const 
    { 
        return groups.at(group); // may throw
    }
    
private:
    string group;
};
 
string formatNum(int num, const string& rep)
{   
    stringstream ss;
    ss.imbue(std::locale(ss.getloc(), 
        new digit_separator(rep)));
    ss << num;
    return ss.str();
}

int main()
{
    cout << formatNum(10000000, "EN") << endl;
    cout << formatNum(10000000, "IN") << endl;
}
