#include <iostream>

using namespace std;

int dmult(int a, int b){
    return 2*a*b;
}

int main(void)
{
    double a = 3.3;
    double b = 2;
    int c = dmult(a,b);
    cout << c << endl;
    return 0;
}