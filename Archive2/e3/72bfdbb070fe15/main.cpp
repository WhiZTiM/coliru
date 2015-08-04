#include <iostream>
#include <string>
#include <locale>
#include <fstream>

int main()
{
    // no conversion is required, just use std::string to hold the bytes in a multi-byte utf-8 string     
    const std::string str = "a \U00000062" // one byte (octect) each
                            " \U000000BE \u011C" // two bytes each (one byte each for space)
                            " \u20AC \U000031F3"  ; // three bytes each (one byte for space)
                        
    
    // input and output work as expected, if we set the stream's locale to a utf-8 locale
    std::cout.imbue( std::locale( "C.UTF-8" ) ) ; // set the stream's locale to UTF-8
    std::cout << str << '\n' ;
    
    std::ifstream this_file( __FILE__ ) ;
    this_file.imbue( std::locale( "C.UTF-8" ) ) ; // set the stream's locale to UTF-8
    std::string line ; 
    for( int i = 0 ; i<5 ; ++i ) if( std::getline( this_file, line ) ) std::cout << i << ". " << line << '\n' ;
    
    std::locale::global( std::locale( "C.UTF-8" ) ) ; // set the default (global) locale if we want utf-8 for all new streams
    std::ofstream( "test_utf8.txt" ) << "file test_utf8.txt: " << str << '\n' ; // the newly-construct stream imbues the global locale
    
    // however, string operations size(), [], substr() etc. operate on bytes and not utf-8 characters
    // and string iterators iterate over each byte, not each utf-8 character.
    std::cout << "size in bytes: " << str.size() << '\n' ; // size in bytes, not characters
    unsigned char c = str[6] ; std::cout << "byte at str[6]: " << std::hex << std::showbase << int(c) << '\n' ; // byte, not character
    for( unsigned char  byte : str ) std::cout << int(byte) << ' ' ; // iterates over bytes, not characters (note: byte-order)
    std::cout << '\n' ;
}
