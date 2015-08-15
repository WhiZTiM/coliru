#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

struct data
{
    static constexpr std::size_t HDR_SIZE = 4 ;
    std::string head[HDR_SIZE] ;

    std::string text ;

    static constexpr std::size_t TAIL_SIZE = 10 ;
    std::string tail[TAIL_SIZE] ;
};

bool get_data( std::string str, data& d )
{
    std::istringstream stm(str) ;
    const auto error = [&d] { d = {} ; return false ; } ;

    // read the header fields
    for( std::string& str : d.head ) stm >> str ;
    if( !stm ) return error() ;

    // read each rmaining white space separated token into a vector
    std::vector<std::string> vec ;
    while( stm >> str ) vec.push_back(str) ;

    const std::size_t n = vec.size() ;
    if( n < data::TAIL_SIZE ) return error() ; // #fields is less than expected

    // extract the last TAIL_SIZE fields into tail in reverse order
    for( std::string& s : d.tail ) { s = vec.back() ; vec.pop_back() ; }
    std::reverse( std::begin(d.tail), std::end(d.tail) ) ; // and reverse the tail

    vec.resize( n - data::TAIL_SIZE ) ; // throw away the extracted fields
    d.text.clear() ; // start with an empty string for text
    // // concatenate the fields that were left
    for( const std::string& str : vec ) d.text += str + ' ' ;
    d.text.pop_back() ; // remove the last extra space

    return true ;
}

int main()
{
    std::istringstream file( "11 03 AC 78 cplusplus is the best 0 1 2 3 4 5 6 7 8 9\n"
                             "83 G 450 A My topics aaa bbb ccc ddd eee fff ggg hhh iii jjj\n"
                             "WQ 3 11 124 UNIX/Linux Programming a0 b1 c2 d3 e4 f5 g6 h7 i8 j9\n" ) ;

    std::string line ;
    data d ;
    while( std::getline( file, line ) && get_data( line, d ) )
    {
        std::cout << "\nhead: " ; for( auto s : d.head ) std::cout << s << ' ' ;
        std::cout << "\n\ntext: '" << d.text << "'\n" ;
        std::cout << "\ntail: " ; for( auto s : d.tail ) std::cout << s << ' ' ;
        std::cout << "\n\n----------------\n" ;
    }

}
