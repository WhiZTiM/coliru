#include <string>
#include <iostream>

using std::cout;
using std::string;
int main()
{
    for (const string& key : {"foo", "bar", "baz"}) {
        cout << key;
    }
}