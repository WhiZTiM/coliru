#include <iostream>
using namespace std;
int main()
{
    int v[10], mais_repete = 0, contador = 0, elemento_repetido; 
	for(int i = 0 ; i < 10 ; i++)
		cin >> v[i];
	elemento_repetido = v[0];
	for (int i = 0; i < 10 ; i++)
	{
		contador = 0;
		for (int j = 0; j < 10 ; j++)
		{
			if (v[i] == v[j])
			{
				contador++;
			}
		}
		if(contador > mais_repete)
		{
			elemento_repetido = v[i];
		}
	}
	cout << elemento_repetido << endl;

	
	return 0;
}

