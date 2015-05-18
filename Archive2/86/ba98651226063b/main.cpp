#include <stdio.h>

int main ()
{
    float v, x;
    
    printf ("Entre com o preço de custo:");
    scanf ("%f", &v);
    
    if (v<'20'){
        x=v*1.45;
        printf ("valor de venda é: %f", x);
    } else
    x=v*1.3;
    printf ("valor de venda é: %f", x);
    
    
    return 0;
}
