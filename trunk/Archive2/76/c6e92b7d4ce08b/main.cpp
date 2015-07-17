#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;

struct mStruct {
    int a;
    char b;
};

mStruct * ring;

void put(const mStruct & item){
    
}

void pull(mStruct & item){
    item = ring[0];
    cout << ring[0].b << endl;
    ring[0].b = 'q';
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
    cout << ring[0].b << endl;
    pull(t);
    ring[0].b='z';
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    //usleep(3000 * 1000);
    cout << t.b << endl;
    cout << ring[0].b << endl;
    

}
