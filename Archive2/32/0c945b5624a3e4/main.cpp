#include <stdio.h>
#include <math.h>
 
int main(void)
{
    // normal use
    printf("cbrt(729) = %f\n", cbrt(729));
    printf("cbrt(-0.125) = %f\n", cbrt(-0.125));
    // special values
    printf("cbrt(-0) = %f\n", cbrt(-0.0));
    printf("cbrt(+inf) = %f\n", cbrt(INFINITY));
}