#include <iostream>

using namespace std ;

int main ()
    {
    int preco;
    int consumo;
    cin >> consumo;
    if(consumo<11) {
        preco=7;
        }else if(consumo<31) {
        preco=7+(consumo-10);
        }else if(consumo<101) {
        preco=7+20+(consumo-30)*2;
        }else {
        preco=7+20+140+(consumo-100)*5;
        }
    cout << preco << endl;
    return 0 ;
    }