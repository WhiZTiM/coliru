#include <iostream>
#include <stdint.h>
using namespace std;

int main()
{
    uint64_t a;
    int b, k, d;
    cin >> a >> b >> k;

    uint64_t x=a;

    for(int i=0;i<b-1;i++)
    {
        x=x*a;   
    }
    d = x % k;

    cout << d;

    return 0;
}