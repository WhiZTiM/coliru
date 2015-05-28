#include <stdio.h>
int main ()
{
    float n1;
    float n2;
    float n3;
    printf("Escreva a nota 1: ");
    scanf("%f", &n1);
    printf("\nEscreva a nota 2: ");
    scanf("%f", &n2);
    printf("\nEscreva a nota 3: ");
    scanf("%f", &n3);
    float media = (2*n1 + 3*n2 + 5*n3)/10;
    printf("\nSua média é %f!", media);
    }