#include <string.h>

     #include <stdio.h>

	 #include <stdlib.h>

	 

	 

	 void shaker(char *items, int count)

	 {

	   register int a;

	   int exchange;

	   char t;

	 

	   do {

	     exchange = 0;

	     for(a=1; a < count; ++a) {

	       if(items[a-1] > items[a]) {

	         t = items[a-1];

	         items[a-1] = items[a];

	         items[a] = t;

	         exchange = 1;

	       }

	     }
printf("partly sorted left2right string is: %s\n", items);

	     for(a=count-1; a > 0; --a) {

	       if(items[a-1] > items[a]) {

	         t = items[a-1];

	         items[a-1] = items[a];

	         items[a] = t;

	         exchange = 1;

	       }

	     }

printf("partly sorted right2left string is: %s\n", items);	 


	   } while(exchange); /* sort until no exchanges take place */

	 }

	 

	 int main(void)

	 {

	 

	   char s[255];

	 

	   printf("Enter a string:");

	   gets(s);

	   shaker(s, strlen(s));

	   printf("The sorted string is: %s.\n", s);

	 

	   return 0;

	 }
