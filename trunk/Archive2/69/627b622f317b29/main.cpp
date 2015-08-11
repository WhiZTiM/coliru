#include <iostream>
#include <sstream>
#include <cctype>

int main()
{
    std::stringbuf sbuf( std::ios::out ) ; // create a stringbuf
    auto oldbuf = std::cout.rdbuf( std::addressof(sbuf) ) ; // associate the stringbuf with std::cout

    std::cout << "hello " << 123 << '\t' << std::fixed << std::showpos << 1235678.9 << " bye!\n\n" ; // use std::cout normally

    std::cout.rdbuf( oldbuf ) ; // restore cout's original buffer

    std::string output = sbuf.str() ; // get a copy of the underlying string
    for( char& c : output ) c = std::toupper(c) ; // modify it
    
    std::cout << output ; // print out the modified output
}
