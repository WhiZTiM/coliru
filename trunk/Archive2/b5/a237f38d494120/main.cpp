#include <iostream>
#include <string>
using namespace std;
struct biblioteca
{
 string titolo;
 string autore;
 int anno;
 string casaeditrice;
 int numeropagine;
};
int main ()
{
 int n,i,max;
 cout<<"di quanti numeri vuoi sapere i dati?"<<endl;
 cin>>n;
 biblioteca libro[n];
 for (i=0;i<n;i++)
 {
  cout<<"Inserisci il titolo del "<<i+1<<"° libro"<<endl;
  cin>>libro[i].titolo;
  cout<<"Inserisci l'autore del "<<i+1<<"° libro"<<endl;
  cin>>libro[i].autore;
  cout<<"inserisci l'anno del "<<i+1<<"°libro"<<endl;
  cin>>libro[i].anno;
  cout<<"inserisci la casa editrice del "<<i+1<<"°libro"<<endl;
  cin>>libro[i].casaeditrice;
  cout<<"inserisci il numero di pagine del "<<i+1<<"°libro"<<endl;
  cin>>libro[i].numeropagine;
 }
 for (int j=1;j<n;j++)
 {
     if (j==1)
      max=libro[j].numeropagine;
     if ((libro[j].numeropagine)>max)
      max=libro[j].numeropagine;
  }
  cout<<"il libro con maggior numero di pagine è"<<max;
return 0;
} 