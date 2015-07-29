#include <cstdio>
#include <cmath>

int main()
{
    float v = 0.123f;
    float epsilon = 0.0001f;
    for(int i=0; i<0xFFFFFFF; ++i)
    {
        if( fabs(((v - static_cast<int>(v)) - 0.123f)) > epsilon)
        {
            printf("%d %.20f\n", i, v);
            break;
        }
        v += 1.f;
    }
    return 0;
}
