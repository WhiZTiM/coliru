#include <iostream>
#include <string>

bool is_double( const std::string& str )
{
    std::size_t pos ;
    try
    {
        std::stod( str, std::addressof(pos) ) ;
        return pos == str.size() ; // entire string has been consumed
    }
    catch( const std::exception& ) { return false ; } // error in conversion
}

int main()
{
    for( std::string str : { "-123.456",  "45fg", "1.0e-23", "inf", "nan", "", "0xab.cdP+55" } )
    std::cout << '"' << str << "\" ? " << std::boolalpha << is_double(str) << '\n' ;
}
