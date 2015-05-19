#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

int main ()
{
    int n, valore, quadrato, cont=0, colore=2;
    
    do
    {
        printf("\nQuanti valori vuoi inserire? ==> ");
        scanf("%d",& n);
    }while(n<=0);
    system("CLS");
    printf("                          Valore     Quadrato");
    while(cont<n)
    {
          
          printf("\nInserisci il %d valore:      ",cont+1);
          
          scanf("%d", & valore);
          quadrato=valore*valore;
          printf("                                        %d",quadrato);
          cont++;
         
          
          
    }
    printf("\n\n");
   
    system("PAUSE");
    
}

