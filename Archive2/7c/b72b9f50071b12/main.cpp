#include <stdio.h>

int main(void) {
   /* variables celcius,faranh,kelvin, que se representan como c,f,k */
   float c, k;
   float f=75.0; 
   /* calculo */
   c=5.0 /9.0 *(f-32);
   k= c+273; 
   printf(" The values of the %f degress Fahrenheit is %f degrees Celsiou "
          "and %f degress Kelvin \n", f,c,k);
   return 0;
}

