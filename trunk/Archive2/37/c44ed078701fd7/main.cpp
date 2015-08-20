#include <iostream>
#include <iomanip>
#include <cmath>
#include <fenv.h>
#pragma STDC FENV_ACCESS ON

using namespace std;
int main()
{
    fesetround(FE_TOWARDZERO);
    cout.precision( 20 );
    float a = 1.0f / 3.0f * 10; //3 1/3
    float b = 2.0f / 3.0f * 10; //6 2/3
    float af = a; // nextafterf( a , 0 );
    float bf = b; // nextafterf( b , 0 );
    cout << a << endl;
    cout << b << endl;
    cout << af << endl;
    cout << bf << endl;
    float sumf = 0.0f;
    for ( int i = 1; i <= 3; i++ )
    {
        sumf = sumf + bf;
        cout << ' ' << sumf << "   == 20 " << (sumf == 20.0f) << '\n';
    }
    sumf = sumf + af;
    cout << sumf << endl;
}
