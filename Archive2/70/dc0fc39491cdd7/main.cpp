#include <stdio.h>

 
int main()
{
unsigned int ip = 123213213;
unsigned char *a = (unsigned char*) &ip;
printf("%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
}