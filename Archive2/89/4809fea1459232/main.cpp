#include <iostream.h>
typedef float vettore[100];
void leggi(int &d,vettore v);
void calcola(int &d,vettore v,float &media);
void stampa(int &d,float &media);

void main()
{
int d,rip;
float media;
vettore v;
do
 {
  cout<<"\n\n ***MEDIA DI N NUMERI***  by Enzo\n";
  leggi(d,v);
  calcola(d,v,media);
  stampa(d,media);
  cout<<"\n\n Vuoi continuare ancora?";
  cout<<"\n si=1 no=0 : ";
  cin>>rip;
  if(rip!=1)
   {
    cout<<"\n\n -----FINE PROGRAMMA-----";
   }
 }
while(rip==1);
}

void leggi(int &d,vettore v)
{
int i;
cout<<"\n\n Quanti sono i numeri per i quali";
cout<<"\n devo calcolare la media?";
do
 {
  cout<<"\n n(max 100 numeri)= ";
  cin>>d;
  if(d>100)
   {
    cout<<"\n ERROR!";
   }
 }
while(d>100);
for(i=0;i<d;i++)
 {
  cout<<"\n\n Inserisci il numero n="<<(i+1)<<" : ";
  cin>>v[i];
 }
}

void calcola(int &d,vettore v,float &media)
{
int i;
media=0;
for(i=0;i<d;i++)
media=media+v[i];
media=media/d;
}

void stampa(int &d,float &media)
{
cout<<"\n\n La media dei "<<d<<" numeri inseriti e':  "<<media;
}
