#include <iostream>
 
using namespace std;

union U1
{
    int a; // 8 bytes
    long double d; // 16 bytes
};

struct S1 { long double a, b; };

struct S2
{
    long double a;
    S1 s;
};

union U2
{
    S2 s1, s2;
    long double a[4];
    long double b;
};

int main()
{
   // Están inicializados a 0.
   U1 u1;
   U2 u2;
   
   cout << sizeof(u1)<< endl;
   cout << sizeof(u2) << endl;
   
   u2.s2.a = 5.;
   u2.s1.s.b = 2.5;
   
   cout << u2.a[0] << " " << u2.a[1] << " " << u2.a[2] << " "
        << u2.a[3] << " " << u2.b << endl;
   
   return 0;
}
