#include <stdio.h>


void float average( float , float , float , float, float *, float * ); // function prototype for average 

 
int main(void) {
  
 float a,b,c,d;
 float suma, average; 

 printf("Enter a 4 float number");
 if (scanf(" %f,%f,%f,%f," &a,&b,&c,&d) !=4) 
   {
    Printf("There was an error, no 4 float number\n");
    return 0;
   }
   
  average(a,b,c,d,&suma,&average,);
  
  Printf("La suma de ,%2.f + %2.f + %2.f + %2.f es %2.f "
       "  Y el average es %3.f", a,b,c,d,suma,average);
  
  
}

// el cuerpo de la funcion prototypo

float average( float num1, float num2 , float num3 , float num4, float *ptr_suma, float *ptr_avg)
{
    
   *ptr_suma = (num1 + num2 + num3 + num4);
   *ptr_avg = *ptr_suma / 4;
}