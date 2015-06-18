#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;


int main()
{

int tab[10];
for(int i=0; i=10; i++ )
{   
    cout<<"Podaj "<<i<<" liczbe: "<<endl;
    tab[i]=i;

}
for (int i=10; i>=0; i--)
{
    cout<<"Liczba "<<i<<" to: "<<tab[i]<<endl;   
}

}
