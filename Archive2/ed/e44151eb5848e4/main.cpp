#include <iostream>
#include <string>
#include <regex>

void display_field( const std::string& text, const std::string& name )
{
    // the field that we are interested in is the marked subexpression ([[:alnum:]]*)
    // ie. zero or more alphanumeric characters immediately after 'name='
    const std::regex regex( name + '=' + "([[:alnum:]]*)" ) ;
    std::smatch match_results ;
    std::regex_search( text, match_results, regex ) ;

    std::cout << "'" << name << "' == " ;
    if( match_results.empty() ) std::cout << "  --- (nonexistent field)\n\n" ;
    else if( match_results[1].length() == 0 ) std::cout << "''  --- (empty field)\n\n" ;
    else std::cout << "'" << match_results[1] << "'  --- (non-empty field)\n\n" ;
}

int main()
{
    const std::string text = "name=etrusks email= posts=168 phone= " ;
    for( std::string fn : { "name", "email", "posts", "age", "phone", "address" } )
        display_field( text, fn ) ;
}
