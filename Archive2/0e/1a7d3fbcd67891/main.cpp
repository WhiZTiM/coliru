#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <fenv.h>
 
#pragma STDC FENV_ACCESS ON
int main(void)

    
    printf("pow(2, 10) = %f\n", pow(2,10));
    printf("pow(2, 0.5) = %f\n", pow(2,0.5));
