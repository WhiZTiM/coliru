#include <stdio.h>

int indiceMin(int const tableau[], int debut, int fin)
{
    int i, j = 0, min = j;
    for(i = debut; i < fin; i++)
    {
        if(j > tableau[i])
            min = tableau[i];
            j = tableau[i];
    }
        return min;
}

int main(){
    int tableau[] = { 3 , 37 , 23 , 7 , 11 , 2 , 17 };
    printf("indice min = %d", indiceMin(tableau, 1, 5));
}