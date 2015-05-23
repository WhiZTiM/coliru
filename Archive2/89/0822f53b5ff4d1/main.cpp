#include <cctype>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/cxx11/all_of.hpp>

using namespace std;
using namespace boost;

//cout << sub[i] << " at " << i << " is not a space."; 

bool isAllSpace(const std::string& s)
{
    for (unsigned i=0; i<s.length(); i++)
    {
        if (!isspace(s[i]))
        {
            return false;
        }
    }
        
    return true;
}
 
int main()
{
    string s = "s)       ;fasdfasd";
    unsigned from  = s.find(')') + 1;
    unsigned count = s.find(';', from) - from;
    
    string sub = s.substr(from, count);
    
    cout << boolalpha << isAllSpace(sub) << endl;
    
    vector<int> v;
    cout << algorithm::all_of(sub, isspace);
}