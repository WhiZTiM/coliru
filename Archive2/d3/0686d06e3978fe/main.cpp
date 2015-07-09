#include <boost/spirit/home/lex.hpp>
#include <boost/spirit/home/lex/lexer_lexertl.hpp>
#include <string>
#include <iostream>

namespace lex = boost::spirit::lex;

typedef lex::lexertl::token< std::string::const_iterator > token;
typedef lex::lexertl::lexer< token > lexer;


enum token_id
{
    byte_order_mark = boost::spirit::lex::min_token_id,
    bad_token
};

class working_lexer : public lex::lexer< lexer >
{
public:
    working_lexer()
    {
        self.add
            ( R"(\xef\xbb\xbf)", byte_order_mark )
            ;
    }
};

class broken_lexer : public lex::lexer< lexer >
{
public:
    broken_lexer()
    {
        self.add
            ( R"(\xef\xbb\xbf)", byte_order_mark )
            // why does the above no longer match once I have one of these?
            //( R"(\/\/[^\n]*|\/\*([^\*]|\*[^\/])*\*\/)", bad_token ) // C-style comments
            ( R"(\"([^\n\"\\]|\\[\"nrt\\])*\")", bad_token ) // ""-strings with \n, \r, \t and \\ escapes
            ;
    }
};

int main( int, char** )
{
    std::string code( "\xef\xbb\xbf" );
    const auto end = code.cend();
    std::cout << "Working lexer:" << std::endl;
    auto it = code.cbegin();
    bool success = lex::tokenize( it, end, working_lexer{} );
    std::cout << "Success: " << std::boolalpha << success << std::endl;
    std::cout << "Consumed everything: " << std::boolalpha << ( it == end ) << std::endl;
    std::cout << "Broken lexer:" << std::endl;
    it = code.cbegin();
    success = lex::tokenize( it, end, broken_lexer{} );
    std::cout << "Success: " << std::boolalpha << success << std::endl;
    std::cout << "Consumed everything: " << std::boolalpha << ( it == end ) << std::endl;
    return 0;
}
