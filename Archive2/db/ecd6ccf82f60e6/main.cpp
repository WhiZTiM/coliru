#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float base=0, altezza=0, totale=0;
    printf("Inserisci la base del triangolo:\n");
    scanf("%f",&base);
    printf("Inserisci l'altezza del triangolo:\n");
    scanf("%f",&altezza);
    totale= (base * altezza) /2;
    printf("La misura dell'area è:,%",totale);
    return 0;
}