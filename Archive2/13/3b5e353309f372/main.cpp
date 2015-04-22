#include <iostream>

using namespace std;

int main ()
    {
    int notaMat,notaPort;
    cin >> notaMat >> notaPort ;
    if (notaMat == 10 &&  notaPort == 10){
        cout << "Excepcional!";
    }else if (notaMat == 10 || notaPort == 10){
        cout << "Parabéns!";
    }else {
        cout << "Estude mais";
    }
    return 0;
    }
