#include <iostream>
#include <string>
#include <vector>


int main()
{
   int a[5]={1,2,3,5,6};
int *apnt= a;
while (*apnt)
{
 printf("The no is %d\n",*apnt);
 apnt++;
}
}
