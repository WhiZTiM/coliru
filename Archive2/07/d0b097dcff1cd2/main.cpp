#include <iostream>

using namespace std ;

int main ()
    {
    int N ;
    cin >> N ;
    if ( (N>=86) && (N<=100) ) {
        cout << "A";
    }else if ( (N>=61) && (N<=85) ) {
        cout << "B" ;
    }else if ( (N>=36) && (N<=60) ) {
        cout << "C" ;
    }else if ( (N>=1) && (N<=35) ) {
        cout << "D" ;
    }else if ( N=0 ) {
        cout << "E" ;
    }
    return 0 ;
    }