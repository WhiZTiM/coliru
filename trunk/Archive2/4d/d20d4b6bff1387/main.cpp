#include <iostream>
#include <string>
using namespace std;

class Player
{
public:
    string pName;
    int team;
};

Player me;
    
void makeClass()
{
    me.pName="TestName";
    cout << me.pName;
}
int main()
{
    makeClass();
}
