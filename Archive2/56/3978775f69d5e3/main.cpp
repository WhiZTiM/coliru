#include <stdio.h>
#include <time.h>
 
int main(void)
{
    time_t now;
    time(&now);
 
    struct tm beg, bog;
    beg = *localtime(&now);
    bog = *localtime(&now);
 
    // set beg to the beginning of the month
    beg.tm_hour = 0;
    beg.tm_min = 0;
    beg.tm_sec = 0;
    beg.tm_mday = 1;
    beg.tm_year = 2014;
 
    beg.tm_hour = 0;
    beg.tm_min = 0;
    beg.tm_sec = 33;
    beg.tm_mday = 1;
    beg.tm_year = 2014;
 
    double seconds = difftime(mktime(&bog), mktime(&beg));
 
    printf("%.f seconds have passed since the beginning of the month.\n", seconds);
 
    return 0;
}