#include <iostream>
using namespace std;

int main()
{
	string A[5]={"lacaxy", "ccafuhuhxy", "apuzkfjnxy","eoifupwoefj", "zaaawroifxy"};
	string s;
	int cont=0;
	int g=0;
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<6; j++)
		{
			int des1=A[i].size()-1;
			int des2=A[j].size()-1;
			if (des1==des2)
			{
				cont++;
			}
		}
	}
	
	if (cont>=3)
	{
		for (int f=0; f<4; f+2)
		{
			s.insert(f,A[g],0,4);
			g++;
		}
		
	}
	
	cout<<s;
	return 0;
}