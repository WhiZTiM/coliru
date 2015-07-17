#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    unsigned short w = 0;
    w = w -1;
    cout << (unsigned int)w << endl;
    cout << "-------" << endl;
    
    char *ring = new char[w];
    ring[0]='a';
    ring[1]='b';
    cout << "[w]:" << w << endl;
    ring[w]='z';
    w++;    cout << "[w]:" << w << endl;
    ring[w]='1';
    w++;    cout << "[w]:" << w << endl;
    ring[w]='2';
    ring[65536] = 'm';
    cout << "65535" << ring[65535] << endl;
    cout << "65536" << ring[65536] << endl;
    cout << "0    " << ring[0] << endl;
    cout << "1    " << ring[1] << endl;

}
