#include <iostream>

using namespace std;

int main ()
    {
    int N;
    int S;
    int menorSaldo=1001;
    int saldoDoDia;
    int cont=0;
    cin >> N >> S;
    while (cont<N) {
        if (S<menorSaldo) {
            menorSaldo=S;
            }
        cin >> saldoDoDia;
        S=S+saldoDoDia;
        cont=cont+1;
    }
    cout << menorSaldo;
    return 0;
    }
