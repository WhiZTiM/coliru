#include <iostream>
#include <string>

std::string student_title( int title_index )
{
    static const int ubound = 4 ;
    static const std::string title[ubound+1] { "Freshman", "Sophomore", "Junior", "Senior", "** invalid **" } ;

    if( title_index < 0 || title_index > ubound ) title_index = ubound ;
    return title[ title_index ] ;
}

void fill_titles( const int title_index[], std::string title_desc[], std::size_t n )
{ for( std::size_t i = 0 ; i < n ; ++i ) title_desc[i] = student_title( title_index[i] ) ; }

int main()
{
    const int number[] { 0, 1, 2, 3, 4, 2, 5, 1, -6, 0, 3 } ;
    const std::size_t sz = sizeof(number) / sizeof( number[0] ) ;

    std::string title[sz] ;
    fill_titles( number, title, sz ) ;

    for( std::size_t i = 0 ; i < sz ; ++i ) std::cout << number[i] << "  " << title[i] << '\n' ;
}
