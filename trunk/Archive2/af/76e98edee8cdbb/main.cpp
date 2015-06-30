#include <iostream>
#include <time.h>

int main()
{
    struct tm currentTime;
    currentTime.tm_year = 2014 - 1990;
    currentTime.tm_mon = 9 - 1;
    currentTime.tm_mday = 6;
    currentTime.tm_hour = 23;
    currentTime.tm_min = 59;
    currentTime.tm_sec = 0;
    currentTime.tm_wday = 7 - 1;
    
    struct tm previousTime;
    previousTime.tm_year = 2014 - 1990;
    previousTime.tm_mon = 9 - 1;
    previousTime.tm_mday = 6;
    previousTime.tm_hour = 23;
    previousTime.tm_min = 58;
    previousTime.tm_sec = 0;
    previousTime.tm_wday = 7 - 1;
    
    std::cout << difftime(mktime(&currentTime), mktime(&previousTime)) << std::endl;
    
    return 0;
}