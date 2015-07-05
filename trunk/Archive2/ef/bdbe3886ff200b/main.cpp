#include <stdio.h> 
#include <stdlib.h>

void bla(int a[]){
    a +=1;
    printf("%d\n", a[0]);
}


int main(void)
{  
    int a = 4, *b, c[4] = {1,2,3};
    a = (*c)++;
    bla(c);
    printf("%d , %d\n", a , *c);
    return 0;
}
