#include <iostream>

using namespace std;

int main ()
    {
    int N;
    int S;
    int base;
    int menorSaldo;
    int cont=0;
    cin >> N >> S;
    base=S;
    menorSaldo=S;
    while (cont<N){
        cin >>S;
        if (menorSaldo<base) {
            menorSaldo=base ;
        }cont=cont+1;
      }
      cout << menorSaldo;
    return 0;
    }