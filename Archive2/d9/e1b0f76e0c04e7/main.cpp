#include <stdio.h>

// Okay, so what if getchar was a macro?
//#define getchar getc(stdin)

int main() {
    int printf = 7;
    int getchar = 6;
    
    char foo[10];
    sprintf(foo, "%d and %d", printf, getchar);
    puts(foo);
    
    
    // your code goes here
	return 0;
}