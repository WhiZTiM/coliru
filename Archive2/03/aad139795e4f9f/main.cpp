#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    std::string tok;
    std::istringstream std_s(str);

    while (getline(std_s, tok, delimiter))
    {
        internal.push_back(tok);
    }
    return internal;
}

int main()
{
    vector<string> v = split("a,b,c,d,e", ',');
    std::cout << v[0] << v[4];
}
