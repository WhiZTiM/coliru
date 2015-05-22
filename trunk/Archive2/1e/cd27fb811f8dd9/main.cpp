
#include <iostream>

using namespace std;

int main ()
    {
    int N;
	int Nvalores;
	int pontos=1;
	int cont=0;
	int base=1;
	int primeiroValor;
	cin >> N;
	cin >> Nvalores;
	primeiroValor=Nvalores;
	while ( cont<(N-1) ) {
	    cin >> Nvalores;
	    if (Nvalores==primeiroValor) {
            base=base+1;
            primeiroValor=Nvalores;
            } else {
                base=1;
                primeiroValor=Nvalores;
            }
            if (base>pontos) {
                    pontos=base;
            }

		cont=cont+1;
	}
	cout << pontos;
	return 0;
	}