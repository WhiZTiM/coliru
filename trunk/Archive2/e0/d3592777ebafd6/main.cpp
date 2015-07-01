#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <stdio.h>
 
int main(void)
{
    time_t t = time(NULL);
    printf("UTC:   %s", asctime(gmtime(&t)));
    printf("local: %s", asctime(localtime(&t)));
 
#ifdef __STDC_LIB_EXT1__
    struct tm buf;
    char str[26];
    asctime_s(str,sizeof str,gmtime_s(&t, &buf));
    printf("UTC:   %s", str);
    asctime_s(str,sizeof str,localtime_s(&t, &buf)));
    printf("local: %s", str);
#endif
}