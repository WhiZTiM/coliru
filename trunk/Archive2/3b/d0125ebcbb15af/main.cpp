#include <iostream>

using namespace std;

int main()
    {
    int contadora=1;
    int n;
    int maiorNumero;
    int numeroLido;
    cin >> n;
    maiorNumero=-1;
    while (n>=contadora){
        cin >> numeroLido;
    if (maiorNumero<numeroLido){
        maiorNumero=numeroLido;
    }
    contadora=contadora+1;
    }
    cout << maiorNumero;
    return 0;
    }
