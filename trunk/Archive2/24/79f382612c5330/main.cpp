#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;


const char chaineBase[50] = "J'aime la programmation!";

char *chaineRenvoye (int N);



int main()
{
    cout << tableauAleatoire (9) << endl;
    return 0;
}

int *tableauAleatoire (int N) {
    int *tab = new int[N];
    int chiffreAleatoire, tmp;

    for (int i = 0 ; i < N ; i++) {
        tab[i] = i;
    }

    srand(time(NULL));
    for (int i = 0 ; i < N ; i++ ) {
        chiffreAleatoire = i + (rand() % (N-i));
        tmp = tab[i];
        tab[i] = tab[chiffreAleatoire];
        tab[chiffreAleatoire] = tmp;
    }

    for ( int i=0 ; i<N ; i++ )
    {
        cout << tab[i] << endl;
    }
}