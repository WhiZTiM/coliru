#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <stdio.h>
 
int main(void)
{
    time_t t = time(NULL);
    //printf("UTC:   %s", asctime(gmtime(&t)));
    //printf("local: %s", asctime(localtime(&t)));
 
    
    struct tm buf;        
    char str[26];


    t = t + 3600;
    

    localtime (&t);
    printf("\next: %u", t);
    
    printf("%s", ctime(&t));

    t = t + 3600;

    localtime (&t);
    printf("\next: %u", t);
    printf("%s", ctime(&t));
    
    t = t + 3600;

    localtime (&t);
    printf("\next: %u", t);
    printf("%s", ctime(&t));    

}