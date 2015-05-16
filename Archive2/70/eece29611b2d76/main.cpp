#include <iostream>

#include <iomanip>

using namespace std;

int main ()
    {
    int cont=0;
    float nota[5];
    int indiceMaiorNota;
    int indiceMenorNota;
    float maiorNota;
    float menorNota;
    float soma=0.0;
    while(cont<5) {
        cin >> nota[cont];
        cont=cont+1;
     }
     indiceMaiorNota=0;
     indiceMenorNota=0;
     maiorNota=4;
     menorNota=11;
     cont=0;
     while(cont<5) {
        if(nota[cont]>maiorNota){
            maiorNota=nota[cont];
            indiceMaiorNota=cont;
            }
        if(nota[cont]<menorNota) {
            menorNota=nota[cont];
            indiceMenorNota=cont;
            }
            cont=cont+1;
     }
     cont=0;
     while(cont<5) {
        if(cont!=indiceMaiorNota && cont!=indiceMenorNota){
            soma=soma+nota[cont];
            }
        cont=cont+1;
     }
     cout<<fixed;
     cout<<setprecision(1);
     cout<<soma;


    return 0;
    }
