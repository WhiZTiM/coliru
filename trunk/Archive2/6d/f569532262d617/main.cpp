#include <iostream>
using namespace std;
int main()
    {
    double operando1;
    double operando2;
    char operador;
    cout << "digite a operação" <<endl;
    cin >> operando1 >> operador >> operando2;
    if( operador=='+'){
        cout << operando1+ operando2;
    }else if(operador== '*'){
        cout << operando1 * operando2;
    }


