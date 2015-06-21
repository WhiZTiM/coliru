#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool has_char( const char* cstr, char c )
{
    if( cstr != NULL )
        for( ; *cstr != 0 ; ++cstr ) if( *cstr == c ) return true ;
    return false ;
}

bool valid_pos( char* cstr, size_t pos ) // return true if pos is valid
{
    if( cstr != NULL )
    {
        size_t sz = 0 ;
        while( cstr[sz] != 0 ) ++sz ;
        return pos < sz  ;
    }
    return false ;
}

void remove_char_at( char* cstr, size_t pos ) // invariant: valid pos
{
    if( cstr != NULL )
    {
        assert( valid_pos( cstr, pos ) ) ; // nop if NDEBUG is defined
        for( ; cstr[pos] != 0 ; ++pos ) cstr[pos] = cstr[pos+1] ;
    }
}

char* squeeze( char* cstr, const char* filter )
{
    if( cstr != NULL && filter != NULL )
    {
        size_t pos = 0 ;
        while( cstr[pos] != 0 )
        {
            if( has_char( filter, cstr[pos] ) ) remove_char_at( cstr, pos ) ;
            else ++pos ;
        }
    }

    return cstr ;
}

int main()
{
    char cstr[] = "abcdefghijklmnopqrstuvwxyz0123456789" ;
    puts(cstr) ;

    const char filter[] = "abra3cadabra79kmtyz" ;
    puts(filter) ;

    puts( squeeze( cstr, filter ) ) ;
}
