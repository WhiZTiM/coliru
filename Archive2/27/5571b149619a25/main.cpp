#include <stdint.h>
#include <stdio.h>

//using value_type = short; // vectorization!
using value_type = int; // no vectorization

uint32_t sum3(value_type* data)
{
    auto data0 = data;
    auto data1 = data + 1000;
    auto data2 = data + 2000;
    auto data3 = data + 3000;
    
    auto aa = 0u;
    auto bb = 0u;
    auto cc = 0u;
    auto dd = 0u;
    
    for (int i = 0; i <= 1000; i += 4)
    {
        aa += data0[i];
        bb += data1[i];
        cc += data2[i];
        dd += data3[i];
    }
    
    return (aa + bb) + (cc + dd);
}
