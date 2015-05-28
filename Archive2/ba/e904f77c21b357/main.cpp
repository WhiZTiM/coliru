#include <stdio.h>
int main ()
{
    int anos;
    int meses;
    int dias;
    printf("Digite sua idade em anos, meses, e dias: ");
    scanf("%d", &anos);
    scanf("%d", &meses);
    scanf("%d", &dias);
    int idade = (365*anos) + (12*meses) + dias;
    printf("\nVocê %d anos, %d meses e %d dias!!", anos, meses, dias);
    printf("\nSua idade em dias é %d!", idade);
    }