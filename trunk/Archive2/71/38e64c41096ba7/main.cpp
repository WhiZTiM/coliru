#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct mStruct {
    int a;
    char b;
};

mStruct * ring;

void temp(mStruct & item){
    item = ring[0];
    return;
}

int main()
{
    unsigned short w = 0;
    w = w -1;
    cout << (unsigned int)w << endl;
    cout << "-------" << endl;
    ring = new mStruct[w+1];
    ring[0].b='a';
    ring[1].b='b';
    ring[2].b='c';
    mStruct t;
    temp(t);
    ring[0].b='z';
    cout << t.b << endl;
    

}
