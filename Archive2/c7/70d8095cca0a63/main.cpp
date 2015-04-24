#include <stdlib.h>
#include <stdio.h>


int main () {
    char* k = malloc(sizeof(int[5]));
    int* a = (int*)(k + 1);
    *a = 5;
}
