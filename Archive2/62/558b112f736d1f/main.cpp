#include <boost/spirit/home/lex.hpp>
#include <boost/spirit/home/lex/lexer_lexertl.hpp>
#include <boost/spirit/home/support/iterators/multi_pass.hpp>
#include <boost/spirit/home/support/iterators/detail/combine_policies.hpp>
#include <boost/spirit/home/support/iterators/detail/no_check_policy.hpp>
#include <boost/spirit/home/support/iterators/detail/ref_counted_policy.hpp>
#include <boost/spirit/home/support/iterators/detail/buffering_input_iterator_policy.hpp>
#include <boost/spirit/home/support/iterators/detail/split_std_deque_policy.hpp>
#include <iterator>
#include <string>
#include <sstream>
#include <iostream>

/// copyable istreambuf iterator
typedef boost::spirit::multi_pass<
    std::istreambuf_iterator< char >,
    boost::spirit::iterator_policies::default_policy<
        boost::spirit::iterator_policies::ref_counted,
        boost::spirit::iterator_policies::no_check,
        boost::spirit::iterator_policies::buffering_input_iterator,
        boost::spirit::iterator_policies::split_std_deque
    >
> iterator;

namespace lex = boost::spirit::lex;

typedef lex::lexertl::token< iterator > token;
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
    std::stringstream code( "\xef\xbb\xbf" );
    iterator it{ std::istreambuf_iterator< char >{ code } };
    iterator end{ std::istreambuf_iterator< char >{} };
    bool success = lex::tokenize( it, end, token_definitions{}, 
        []( const token& t )
        {
            std::cout << "tokenized BOM: " << std::boolalpha << ( t.id() == byte_order_mark ) << std::endl;
            return true;
        }
    );
    std::cout << "Success: " << success << std::endl;
    std::cout << "Consumed everything: " << ( it == end ) << std::endl;
    return 0;
}
