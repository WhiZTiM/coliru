#include <stdlib.h>
#include <stdio.h>
 
void f1()
{
    puts("pushed first");
    fflush(stdout);
}
 
void f2()
{
    puts("pushed second");
}
 
int main(void)
{
    at_quick_exit(f1);
    at_quick_exit(f2);
    quick_exit(0);
}