#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void encrypt(std::string &iostr, int key) 
{
    key %= 26;
    int ch;
    for (auto &it : iostr) 
    {
        ch = tolower(it);
        if (!islower(ch)) 
        {
           continue;
        }
        ch += key;
        if (ch > 'z') 
        {
            ch -= 26;
        }
        it = ch;
    }
}

int main() 
{
    string source;
    int key = 1;
    cout << "Paste cyphertext and press enter to shift each letter right 1";
    getline(cin, source);
    encrypt(source, key);
    cout << source << "";
    encrypt(source, key);
    cout << source << endl;
    cout << "Press ENTER to exit";
    cin.ignore(cin.rdbuf()->in_avail() + 1);
    return 0;
}