#include <stdlib.h>
#include <stdio.h>

int main() {   
    int *a, *b;
    //a = (int *)malloc(sizeof(int));
    //*a = 10;
    b = a;
    
    printf("%d\n", b);
    printf("%d\n", a);
}