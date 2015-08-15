#include <iostream>

std::size_t len( const char* cstr )
{
    std::size_t n = 0 ;
    if( cstr != nullptr ) while( *cstr++ ) ++n ;
    return n ;
}

char* cat_dot(const char* s1, const char* s2, const char* s3)
{
    char* p = new char[ len(s1) + len(s2) + len(s3) + 1 ]; // +1 for null terminator

    char* temp = p ;

    if(s1) while(*s1) *temp++ = *s1++ ;
    if(s2) while(*s2) *temp++ = *s2++ ;

    if(s3) while( ( *temp++ = *s3++ ) ) ; // null terminate

    return p;
}

int main()
{
    std::cout << cat_dot( "Napoleone", " | ", "Boneparte" ) << '\n'
              << cat_dot( "Napoleone", "|", "Boneparte" ) << '\n'
              << cat_dot( "Napoleone", nullptr, "Boneparte" ) << '\n' ;
}
