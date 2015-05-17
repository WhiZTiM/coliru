#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
 
int main(void)
{
    const char *p = "0x83b850aed5da0853";
    printf("Parsing '%s':\n", p);
    long i = strtol(p, NULL, 16);

    printf("%ld\n", i);
}