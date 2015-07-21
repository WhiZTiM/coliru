#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <stdio.h>
 
int main(void)
{
    time_t t = time(NULL);
    time_t myTime;
    printf("UTC:   %s", asctime(gmtime(&t)));
    printf("local: %s", asctime(localtime(&t)));
    struct tm * timeinfo;
    time (&myTime);
    timeinfo = localtime(&myTime);
    printf(" [%.2d/%.2d/%d %.2d:%.2d:%.2d] ", timeinfo->tm_mday, timeinfo->tm_mon+1, 1900+timeinfo->tm_year, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
 printf("\n\n\nCurrent time = %s", ctime(&myTime));
#ifdef __STDC_LIB_EXT1__
    struct tm buf;
    char str[26];
    asctime_s(str,sizeof str,gmtime_s(&t, &buf));
    printf("UTC:   %s", str);
    asctime_s(str,sizeof str,localtime_s(&t, &buf)));
    printf("local: %s", str);
#endif
}