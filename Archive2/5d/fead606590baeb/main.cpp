// required magic!
#define __STDC_WANT_LIB_EXT1__ 1

#include <time.h>
#include <stdio.h>

int main()
{
    char s[50];
    time_t  t = time( NULL );
    int e ; // int e instead of errno_t e to avoid the error: errno_t was not declared
    e = ctime_s( s, 50, &t );                           // 
    if( e ) puts( "fooey!" ) ;
    else puts(s);
}
