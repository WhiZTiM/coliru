#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

unsigned int htoui( const char* restrict hexdigits )
{
    if( hexdigits == NULL ) { errno = EINVAL ; /* bsd */ return 0 ; }
    
    // http://en.cppreference.com/w/c/string/byte/strtoul
    char* p = NULL ;
    errno = 0 ;
    const unsigned long v = strtoul( hexdigits, &p, 16 ) ;

    if( errno != 0 ) return 0 ; // strtol failed
    
    if( *p != 0 ) { errno = EINVAL ; /* bsd */ return 0 ; } // not fully parsed
    
    if( v > UINT_MAX ) { errno = ERANGE ; return 0 ; } // out of range

    return v ;
}

int main()
{
    const char* const test[] = { "ffff", "0x82345678", "123", "123x", "0x1234567890ab", NULL } ;
    enum { N = sizeof(test) / sizeof(*test) }; 
    
    for( int i = 0 ; i < N ; ++i )
    {
        unsigned int value =  htoui( test[i] ) ;
        printf( "str: '%s' int: %u 0x%x (status: %s)\n", ( test[i] ? test[i] : "NULL" ), value, value, strerror(errno) ) ;
    }
}
