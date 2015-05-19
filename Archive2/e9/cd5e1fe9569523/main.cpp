#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

const char* skip_prefix( const char* hexstr )
{
    if(hexstr)
    {
        while( isspace(*hexstr) ) ++hexstr ; // skip leading whitespace

        char c = *hexstr ;

        if( c == 0 ) return NULL ;
        else if( c == '0' )
        {
           c = *++hexstr ; // skip leading zero
           if( c == 'x' || c == 'X' ) ++hexstr ; // skip leading 0x 0X
        }
    }

    return hexstr ;
}

int value( char digit )
{
    if( digit >= '0' && digit <= '9' ) return digit - '0' ;

    digit = tolower(digit) ;
    switch(digit)
    {
        case 'a' : return 10 ;
        case 'b' : return 11 ;
        case 'c' : return 12 ;
        case 'd' : return 13 ;
        case 'e' : return 14 ;
        case 'f' : return 15 ;
    }
    return -1 ;
}

unsigned int hexstr_to_uint( const char* hexstr )
{
    hexstr = skip_prefix(hexstr) ;
    if( !hexstr ) { errno = EINVAL ; return 0 ; } // null pointer

    // static assertion: long_long_is_bigger_than_int
    enum { assume_long_long_is_bigger_than_int = 1 / ( sizeof(long long) - sizeof(int) ) } ;
    unsigned long long number = 0 ;

    int digit_value = 0 ;

    for( ; ( digit_value = value(*hexstr) ) != -1 ; ++hexstr )
    {
        number *= 16 ;
        number += digit_value ;
        if( number > UINT_MAX ) { errno = ERANGE ; return 0 ; } // out of the range of unsigned int
    }

    if( *hexstr != 0 ) { errno = EINVAL ; return 0 ; } // not fully parsed

    return number ;
    
    // TODO:
    // 1. support optional integer-literal-suffix 
    // 2. allow optional unary + or - operators (leading sign)
}

int main()
{
    const char* const test[] = { "ffff", "0x0001", "0X0082345678", "0129", "129x", "0x100000000", NULL, "00001" } ;
    enum { N = sizeof(test) / sizeof(*test) };

    for( int i = 0 ; i < N ; ++i )
    {
        errno = 0 ;
        unsigned int value =  hexstr_to_uint( test[i] ) ;
        printf( "\nstr: '%s' => uint: %u 0x%x   status: %s\n",
                ( test[i] ? test[i] : "NULL" ), value, value, strerror(errno) ) ;
    }
}
