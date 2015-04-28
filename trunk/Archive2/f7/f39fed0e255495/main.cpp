#include <stdio.h>
int main()
{
 int i, tab, num;
 printf("Tabuada de: ");
 scanf("%d", &tab);
 printf("Até qual número: ");
 scanf("%d", &num);
 for(i = 1; i <= num; i++)
 {
 printf("%d x %d = %d\n", i, tab, i * tab);
 }
 return 0;
}