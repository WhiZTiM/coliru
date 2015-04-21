#include <string>
#include <iostream>
#include <vector>

using namespace std;

void prnt(string str)
{
    cout << str << endl;
}

void check(int val)
{
    if(val == 0)
        cout << "equal" << endl;
    else if(val < 0)
        cout << "lesser" << endl;
    else
        cout << "greater" << endl;
}

struct Container
{
    Container() : str(nullptr) {}
    string* str;
};

int main()
{
    string s1 = "4xILASs5dmhcexwgWLIf6MJiKuA";
    string s2 = "4XILASs5dmhcexwgWLIf6MJiKuA";
    
    Container cont;
    if(!cont.str) cout << "string pointer not initialized" << endl;
    cont.str = new string;
    if(cont.str) cout << "string pointer initialized" << endl;
    *cont.str = s1;
    check((*cont.str).compare(s1));
    check((*cont.str).compare(s2));
}
