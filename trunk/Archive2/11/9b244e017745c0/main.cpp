#include <stdio.h>

void inverse(int i, int j)
{
    {
        int temp = i;
        i = j;
        j = temp;
    }
}
 
int main(){
   int a = 17;
   int b = 23;
   
   printf("a = %d ; b = %d\n", a, b);
   inverse(a, b);
   printf("inverse\n");
   printf("a = %d ; b = %d\n", a, b);
}