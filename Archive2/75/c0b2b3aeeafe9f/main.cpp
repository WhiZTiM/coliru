
#include <iostream>

using namespace std;

int main ()
    {
	int N;
	int Nvalores;
	int pontos=0;
	int cont=0;
	int base=0;
	cin >> N;
	cin >> Nvalores;
	while (cont<N) {
		if (Nvalores!=pontos) {
			pontos=Nvalores;
			base=base+1;
		} else {
			pontos=0;
		}
		cont=cont+1;
	}
	cout << base;
	return 0;
	}