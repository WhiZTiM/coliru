#include <iostream>
using namespace std;

int main()
{
   int  numero1,numero2;
   cout<<"inserisci il numero 1 \n";
   cin>>numero1;
   cout<<"inserisci il numero 2  \n";
   cin>>numero2;
   if(numero1==numero2)
    {
        cout<<"sono uguali";
    };
    if(numero1>numero2)
    {
        cout<<"il numero 1 è maggiore";
    }
    else
    {
        cout<<"il numero 2 è maggiore";
    };
   return 0;
  
}
