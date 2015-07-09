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
};

class token_definitions : public lex::lexer< lexer >
{
public:
    token_definitions()
    {
        self.add
            ( R"(\xef\xbb\xbf)", byte_order_mark )
            ;
    }
};

int main( int, char** )
{
    std::string code( "\xef\xbb\xbf" );
    auto it = code.cbegin();
    bool success = lex::tokenize( it, code.cend(), token_definitions{}, 
        []( const token& t )
        {
            std::cout << "tokenized BOM: " << std::boolalpha << ( t.id() == byte_order_mark ) << std::endl;
            return true;
        }
    );
    std::cout << "Success: " << success << std::endl;
    std::cout << "Consumed everything: " << ( it == code.cend() ) << std::endl;
    return 0;
}
