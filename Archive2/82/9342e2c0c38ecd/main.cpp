#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string principal_period(const string& s)
{
    size_t i = (s+s).find(s, 1);
    return s.substr(0,i);
}

int main()
{
    cout << principal_period("01230123") << endl;
    return 0;
}
