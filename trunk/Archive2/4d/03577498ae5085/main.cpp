#include <stdio.h>

  int main(void) {
  float largo, ancho, area;
  
  printf(" favor digitar el ancho: ");
  
  if (scanf("%f", &ancho) != 1){   // importante de usar el & xq con eso nos da la dirección de memoria
   printf("el ancho %f es incorrecto",ancho);
   return 1;
  }

 printf(" favor digitar el largo: ");
  
  if (scanf("%f", &largo) != 1){
   printf("el largo %f es incorrecto",largo);
   return 1;
  }

  area = largo * ancho;
  printf("El triangulo tine un ancho %f y un largo %f"
         " el area es de %2.2f\n", ancho,largo,area );  // %2.2f   esto es para que de solo 2 numeros y 2 decimales

}