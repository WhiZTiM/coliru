#include <stdio.h>
 
int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    int ndx = 0;
    while (ndx < argc)
    {
          printf("argv[%d] --> %s\n", ndx,argv[ndx]);
          ++ndx;
    }
    printf("argv[argc] = %s\n", argv[argc]);
    return 0;
}