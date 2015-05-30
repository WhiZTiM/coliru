#include <iostream>

using namespace std;

int main()
{
    //variabili
    int scelta;
    bool error = false;
    
    //menu di scelta
    do{
        cout << (error ? "Errore: inserisci un numero del menu" : "") 
            << "\n1. Eleva a potenza due numeri"
            << "\n2. Calcola il fattoriale di un numero"
            << endl;
        cin >> scelta;
    }while(false);
    //}while(scelta < 1 || scelta > 2);
    cout << scelta;
    
    //
    
   return 0;
}

