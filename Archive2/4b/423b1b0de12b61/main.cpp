#include <stdio.h>
#include <stdlib.h>


int a=0;
int totalna=0; //total numero de articulos   
int totalinva=0; // total invertido
int ganancia=0; 
int i=0;
int x=0;

struct agenda{
char codigo[25];
int cantidad;
int precio_por_articulo;
char tipo_de_articulo [15];
char nombre_articulo [20];
int precio_para_venta ;

};
int main (){
int totalinvaux=0; // aux total para invertido por articulo
int auxprecioventa=0;
int auxprecioventa2=0;
    struct agenda amigos;
   
    printf("\n INGRESAR DATOS DE LOS ARTICULOS \n\n ");
    printf("\n CUANTOS ARTICULOS DESEA INGRESAR \n\n ");
     scanf("%d",&a);
     
for(i=1; i<=a; i++) {
    printf("\n ingrese el codigo \n");
    scanf("%s",amigos.codigo);
    
      printf("\n ingrese la cantidad de articulos\n");
    scanf("%d",&amigos.cantidad);
       
    printf("\n ingrese el precio por articulo \n");
    scanf("%d",&amigos.precio_por_articulo);
    
     printf("\n ingrese el tipo de articulo \n");
    scanf("%s",amigos.tipo_de_articulo);
    
     printf("\n ingrese el nombre de articulo  \n");
    scanf("%s",amigos.nombre_articulo);
    
      printf("\n ingrese el precio para la venta de los articulos \n");
    scanf("%d",&amigos.precio_para_venta);
     
totalna=totalna+amigos.cantidad;
totalinvaux=amigos.precio_por_articulo*amigos.cantidad;
totalinva=totalinva+totalinvaux;
auxprecioventa2=amigos.precio_para_venta*amigos.cantidad;
auxprecioventa=auxprecioventa+auxprecioventa2;

}

ganancia= auxprecioventa-totalinva;

  printf("ganancia  %d \ntotal invertido %d \ntotal numero de articulos %d\n", ganancia, totalinva, totalna);



 system("PAUSE()");

}
