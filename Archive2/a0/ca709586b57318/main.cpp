// required magic!
#define __STDC_WANT_LIB_EXT1__ 1

#include <ctime>
#include <iostream>

int main()
{
    char s[50];
    std::time_t  t = std::time( NULL );
    int e ; // int e instead of errno_t e to avoid the error: errno_t was not declared
    e = ctime_s( s, 50, &t ); // *** error: 'ctime_s' was not declared in this scope                             // 
    if( e ) std::cout << "fooey!\n";
    else   std::cout << s;
}
