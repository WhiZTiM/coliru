#include <iostream>
#include <string>

bool is_double( const std::string& str )
{
    std::size_t pos ;
    try
    {
        // http://en.cppreference.com/w/cpp/string/basic_string/stof        
        std::stod( str, std::addressof(pos) ) ;
        return pos == str.size() ; // entire string has been consumed
    }
    catch( const std::exception& ) { return false ; } // no conversion or out of range of double
}

int main()
{
    for( std::string str : { "-123.456",  "45fg", "1.0e-234", "inf", "nan", "", "0xab.cdP+55", "1.e+1234" } )
    std::cout << '"' << str << "\" ? " << std::boolalpha << is_double(str) << '\n' ;
}
