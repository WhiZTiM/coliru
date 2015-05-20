#include <string>
#include <sstream>
#include <iostream>

union UPtrMem
{
    void* p;
    char ach[sizeof(void*)];
};

int main(int argc, char** argv) {
    

    UPtrMem u;
    u.p = nullptr;
    u.p++;      // UB according to standards
    u.ach[0]++; // why is this OK then??
    
}