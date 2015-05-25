#include <iostream>
#include <fstream.h>

using namespace std;

int main()
{
    string P;
    cout << "Inserire percorso file:" << endl;
    cin >> P;
    ofstream f(P, ios::app);
    if(!f) {
        cout< <"Il file non esiste!";
        return -1;
    }
    while(f.good()) //fino a quando c'è qualcosa da leggere ..
    {
        getline(f, s); //legge tutta la riga dal file e la mette nella variabile s
        cout<<s<<endl;
    }
    f.close();
    return 0;
}

