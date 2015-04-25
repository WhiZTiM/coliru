#include <iostream>

using namespace std ;

int main ()
    {
    float X,Y;
    char C;
    cin >> X >> C >> Y;
    cout.precision(3);
    if (C=='+'){
    cout << X+Y;
    }else if (C=='-'){
    cout << X-Y;
    }else if (C=='*'){
    cout << X*Y;
    }else if (C=='/'){
    cout << X/Y;
    }

    return 0 ;
    }
