include <stdio.h>
int main() {

   int arranjo[5] = { 2, 4, 3, 1, 5 };

   printf("%p\n", arranjo);      /* imprime o endereço do arranjo                                                              */
   printf("%d\n", arranjo[0]);   /* imprime o primeiro elemento do arranjo, 2                                                  */
   printf("%d\n", *arranjo);     /* imprime o primeiro inteiro do endereço apontado pelo arranjo, que é o primeiro elemento, 2 */
   printf("%d\n", arranjo[3]);   /* imprime o quarto elemento do arranjo, 1                                                    */
   printf("%p\n", arranjo+3);    /* imprime o terceiro endereço após o início do arranjo                                       */
   printf("%d\n", *(arranjo+3)); /* imprime o valor no tercero endereço após o início do arranjo, 1                            */

   return 0;
}