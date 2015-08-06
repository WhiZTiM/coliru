#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <cctype>

int main()
{
    std::map< std::pair<int, std::string>, std::string > ou_and_area_to_tech_map
    {
        { { 101, "denver" }, "Michael McDonald" },
        { { 102, "oklahoma" }, "Mickey Mouse" },
        { { 103, "dallas" }, "Woody Woodpecker" },
        // ...
    };

    const std::string ou_str = "102" ;
    std::string area = "OKLAHOMA" ;

    for( char& c : area ) c = std::tolower( c ) ;
    int ou = 0 ;
    try { ou = std::stoi( ou_str ) ; }
    catch( const std::exception& ) { std::cerr << "invalid ou\n" ; return 1 ; }

    auto iter = ou_and_area_to_tech_map.find( { ou, area } ) ;
    if( iter != ou_and_area_to_tech_map.end() ) std::cout << "tech is '" << iter->second << "'\n" ;
    else std::cerr << "invalid ou/area '" << ou_str << '/' << area << "'\n" ;
}
