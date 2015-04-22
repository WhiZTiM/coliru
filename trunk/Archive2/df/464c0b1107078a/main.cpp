#include <iostream>

using namespace std;

int main()
    {
    int x,y;
    cin >> x >> y;
    if ((x>=0 && x<=432) && (y>=-468 && y<=468)){
    cout << "dentro";
    }else{
    cout << "fora";
    }
    return 0;
    }
