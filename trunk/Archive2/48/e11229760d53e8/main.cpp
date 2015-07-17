#include <iostream>
#include <string>
#include <vector>
//#include <chrono>
//#include <thread>
//#include <unistd.h>

using namespace std;

struct mStruct {
    int a;
    char b;
};

mStruct * ring;

void put(const mStruct & item){
    ring[0] = item;
}

void pull(mStruct & item){
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
    
    mStruct data;
    mStruct t;
    data.b = 'a';
    cout << "data=" << data.b << ", ring[0]=" << ring[0].b << /*", t=" << t.b <<*/ endl;
    ring[0].b = 'z';
    cout << "data=" << data.b << ", ring[0]=" << ring[0].b << /*", t=" << t.b <<*/ endl;
    put(data);
    cout << "data=" << data.b << ", ring[0]=" << ring[0].b << /*", t=" << t.b <<*/ endl;
    data.b = 'b';
    cout << "data=" << data.b << ", ring[0]=" << ring[0].b << /*", t=" << t.b <<*/ endl;
    ring[0].b = 'c';
    cout << "data=" << data.b << ", ring[0]=" << ring[0].b << /*", t=" << t.b <<*/ endl;    
    pull(t);
    cout << "data=" << data.b << ", ring[0]=" << ring[0].b << ", t=" << t.b << endl;
    t.b = 'n';
    cout << "data=" << data.b << ", ring[0]=" << ring[0].b << ", t=" << t.b << endl;
    delete[] ring;
    cout << "data=" << data.b << /*", ring[0]=" << ring[0].b <<*/ ", t=" << t.b << endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    //usleep(3000 * 1000);
}
