#include <iostream>
#include <map>
#include <string>
#include <cctype>

std::string to_lower( const std::string& str )
{
    std::string lc ;
    for( char c : str ) lc += std::tolower(c) ;
    return lc ;
}

std::map< std::string, std::string > to_lower( const std::map< std::string, std::string >& map )
{
    std::map< std::string, std::string > lc ;
    for( const auto& pair : map ) lc.emplace( to_lower(pair.first), to_lower(pair.second) ) ;
    return lc ;
}

int main()
{
     std::map< std::string, std::string > the_sms_codes
     {
        { ".02",  "Your (or my) two cents worth" },
        { "10X",  "Thanks" },
        { "2MI",  "Too much information"},
        { "2U2",  "To You Too" },
        { "4COL", "For Crying Out Loud" }
     };

     the_sms_codes = to_lower(the_sms_codes) ;

     for( const auto& pair : the_sms_codes ) std::cout << pair.first << " - " << pair.second << '\n' ;
}
