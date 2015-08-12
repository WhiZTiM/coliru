// to fix compile error 
// 1. g++ -std=c++11

#include <stdlib.h>
#include <stdio.h>


float get_float(float f) {
    return f*f;
}

#define SomeFloat 0.5
static const int SomeIntConst = ((int)(SomeFloat+0.5));

template<int V>
struct SomeStruct {
};

int main(int argc, char* argv[]) {
    SomeStruct<SomeIntConst>();
    float fv = (float)(argc);
    const float cf = get_float(fv);
    printf("%f\n",cf);
    return 0;
}
