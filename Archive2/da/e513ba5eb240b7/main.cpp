#include<stdio.h>
#include<stdlib.h>
// dichiarazioni variabili
int a,b,somma;
int main()
{
    printf("inserisci il primo numero:");
    scanf("%d",&a);
    printf("inserisci il secondo numero:");
    scanf("%d",&b);
    
    somma=a+b;
    printf("la somma dei due numeri inseriti è: %d",somma);
}