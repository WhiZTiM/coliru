#include <iostream>
using namespace std;

bool ricorsione(char*,char*,char*,int,int,int,int);
int main()
{
	int n,n1;
	cout<<"Inserisci la dimensione dell' array A e dell' array B: ";
	cin>>n;
	
	char*A=new char [n];
	char*B=new char [n];
	
	cout<<"Introduci elementi nell'array A: "<<endl;
	for (int i=0; i<n; i++)
	{
		cin>>A[i];
	}
	
	cout<<"Introduci elementi nell'array B: "<<endl;
	for (int j=0; j<n; j++)
	{
		cin>>B[j];
	}
	
	cout<<"Inserisci la dimensione dell'array C: "<<endl;
	cin>>n1;
	
	char* C=new char [n1];
	
	int i=0,j=(n-1);
	
	if (ricorsione(A,B,C,i,j,n,n1))
	{
		cout<<"TRUE";
	}
	
	else
	{
		cout<<"FALSE";
	}
	
	return 0;
	 
}

bool ricorsione (char* A,char* B,char* C,int i,int j,int n,int n1)
{
	int c=0;
	
	if (i==(n-1) && j==0 && c==(n1-2))
	{
		C[c]=A[i];
		C[c+1]=B[j];
		return true;
	}
	
	else
	{
		if (n1==(2*n))
		{
			C[c]=A[i];
			C[c+1]=B[j];
			c+=2;
			return ricorsione(A,B,C,i++,j--,n,n1);
		}
		
		else
		{
			return false;
		}
	}
}