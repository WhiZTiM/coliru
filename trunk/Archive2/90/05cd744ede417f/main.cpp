#include <stdio.h>
#include <time.h>
#include <stdint.h>
 
int main(void)
{
    time_t result = time(NULL);
    if(result != -1)
        printf("The current time is %s(%ju seconds since the Epoch)\n",
               asctime(gmtime(&result)), (uintmax_t)result);
}