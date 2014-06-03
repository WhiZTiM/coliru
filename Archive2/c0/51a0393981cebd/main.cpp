#include <stdio.h>
#include <time.h>
 
int main()
{
    time_t now;
    time(&now);
 
    struct tm beg;
    beg = *localtime(&now);
 
    // set beg to the beginning of the month
    beg.tm_hour = 0;
    beg.tm_min = 0;
    beg.tm_sec = 0;
    beg.tm_mday = 1;
 
    double seconds = difftime(now, mktime(&beg));
 
    printf("%.f seconds have passed since the beginning of the month.\n", seconds);
 
    return 0;
}