
#include <iostream>

using namespace std;

int main ()
    {
    int C,N;
	int resultado1;
	int resultadoFinal;
	cin >> C >> N;
	resultado1=( ((C/N)*N) );
	resultadoFinal=C-resultado1;
	cout <<resultadoFinal;
	return 0;
	}