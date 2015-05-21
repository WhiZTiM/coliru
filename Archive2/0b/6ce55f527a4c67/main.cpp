#include <stdio.h>
#include <conio.h>
#include <math.h>

int main(){
   double a,d=0,c=0,b,m,j,s;
   do
   {
   printf("introduce un valor");
   scanf_s("%lf",&a);
   d=d+1;
   c=a+c;
   printf("deseas inglresar otro datomsi=1 no=0");
   scanf_s("%lf",&b);
   }
   while(b>=1);
   { m=c/d;
    printf("introduce el valor que desea ver el porsentaje de desviasion");
     scanf_s("%lf",&j);
     s=100*((m-j)/m);
     printf("el porcetaje de la desviacion es% %lf",s);
   }
   _getch ();
}