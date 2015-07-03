#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

int f(char*p, char*s)
{
    if(*p=='\0') return 1;
    if(*p!=*s) return 0;
    return f(p+1,s+1);
    }
    
int main()
{
   char* s1="non reciderci forbice quel volto";
   char* s2="ci";
   int i;
   printf("2: %i\n", f(s2,s1+4));
   printf("1: %i\n", f(s2,s1));
   printf("1: %i\n", f(s2,s1+6));
   printf("----------\n");
   for(i=0;i<strlen(s1);i++)
      if(f(s2,s1+i))
         printf("%i\n",i);
}
