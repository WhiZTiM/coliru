#include <stdio.h>
#include <time.h>
 
int main(void)
{
    struct tm start = {.tm_mday=1};
    mktime(&start);
    printf("%s\n", asctime(&start));
}