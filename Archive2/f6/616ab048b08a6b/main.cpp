#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string principal_period(const string& s)
{
    return s.substr(0,(s+s).find(s, 1));
}

int main()
{
    cout << principal_period("01230123") << endl;
    cout << principal_period("abcdefabcdefabcdef") << endl;
    return 0;
}
