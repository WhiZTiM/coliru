#include <boost/spirit/home/lex.hpp>
#include <boost/spirit/home/lex/lexer_lexertl.hpp>
#include <boost/spirit/home/support/iterators/multi_pass.hpp>
#include <boost/spirit/home/support/iterators/detail/combine_policies.hpp>
#include <boost/spirit/home/support/iterators/detail/no_check_policy.hpp>
#include <boost/spirit/home/support/iterators/detail/ref_counted_policy.hpp>
#include <boost/spirit/home/support/iterators/detail/buffering_input_iterator_policy.hpp>
#include <boost/spirit/home/support/iterators/detail/split_std_deque_policy.hpp>
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

class token_definitions : public lex::lexer< lexer >
{
public:
    token_definitions()
    {
        self.add_pattern
            ( "HEX", "[0-9a-zA-Z]" )
            ;
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
    auto it = code.cbegin(), end = code.cend();
    bool success = lex::tokenize( it, end, token_definitions{}, 
        []( const token& t )
        {
            std::cout << "tokenized BOM: " << std::boolalpha << ( t.id() == byte_order_mark ) << std::endl;
            return true;
        }
    );
    std::cout << "Success: " << std::boolalpha << success << std::endl;
    std::cout << "Consumed everything: " << std::boolalpha << ( it == end ) << std::endl;
    return 0;
}
