#include <stdio.h> 
#include <stdlib.h>

int main(void)
{  
    int a = 5;
    int a1[10] = {0};
    int* a2[10] = {0};
    a2[0] = 5;
    a1[0] = &a;
    return 0;
}
