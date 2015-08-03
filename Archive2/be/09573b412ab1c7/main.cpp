#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <stdio.h>
 
int main(void)
{
    struct tm current_tmDatetime;
    current_tmDatetime.tm_sec = 0;
    current_tmDatetime.tm_min = 0;
    current_tmDatetime.tm_hour = 23;
    current_tmDatetime.tm_mday = 31;
    current_tmDatetime.tm_mon =  7;
    current_tmDatetime.tm_year = 2015-1900;
    
    time_t t = mktime(&current_tmDatetime);
    printf("%s", ctime(&t));
    if (t == -1)
    {
        printf("Time_t null");        
    }
    //time_t t = time(&tmt);

   t = t + 3600;
   t = t + (3600*24);    
   printf("%s", ctime(&t));
   
   struct tm *mytm = localtime( &t );
   
   printf(" %d ",mytm->tm_year+1900);
   printf(" %d ",mytm->tm_mon+1);
   printf(" %d ",mytm->tm_mday);
   printf(" %d ",mytm->tm_hour);
   
   
   
    
}