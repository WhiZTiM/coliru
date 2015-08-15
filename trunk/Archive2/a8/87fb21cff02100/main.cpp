// header (add comments)
#include <stdbool.h>

int my_getc() ;
bool my_ungetc( char c ) ;
bool my_ungets( const char* cstr ) ;


// implementation

// #include header
#include <stdio.h>
#include <string.h>

enum { BUFFSZ = 100 };
static char buffer[BUFFSZ] = {0};
static size_t next_pos = 0 ;  /* next free position in buf */

static bool empty() { return next_pos == 0 ; }
static size_t available() { return BUFFSZ - next_pos ; }
static char pop() { return empty() ? 0 : buffer[--next_pos] ; }
static bool push( char c ) { return available() ? ( buffer[next_pos++] = c ) : false ; }


int my_getc() { return empty() ? getchar() : pop() ; }

bool my_ungetc( char c ) { return push(c) ; }

bool my_ungets( const char* cstr )
{
    if( cstr == NULL ) return false ;
    const size_t len = strlen(cstr) ;
    if( len > available() ) return false ;

    // loop through the string and push in reverse order
    for( size_t i = 0 ; i < len ; ++i ) my_ungetc( cstr[ len-1-i ] ) ;
    return true ;
}

int main()
{
    const char a[] = "test ungets();" ;
    const char b[] = "test it once again." ;

    if( my_ungets(b) && my_ungetc(' ' ) && my_ungets(a) )
        for( size_t i = 0 ; i < ( sizeof(a)-1 + 1 + sizeof(b)-1 ) ; ++i ) putchar( my_getc() ) ;

    if( my_ungetc('\n') ) putchar( my_getc() ) ;
}
