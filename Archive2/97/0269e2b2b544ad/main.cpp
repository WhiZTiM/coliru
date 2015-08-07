#include<iostream>
using namespace std;
int main()
{
    int x = 1, y = 1, i, j;
    float a[3][3], p;
    i = x;
    j = y;
    p = 1.4;
    a[i+1][j] = 3.5;
    a[1][1] = -2.5;
    a[i + 1][j] = a[x][j] * p + a[i+1][j];
    cout<<a[i+1][j];

    return 0;
}
