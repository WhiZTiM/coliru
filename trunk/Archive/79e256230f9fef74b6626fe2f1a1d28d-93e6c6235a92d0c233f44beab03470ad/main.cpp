#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_container.hpp>

#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <cassert>

using namespace boost::spirit;

enum tokenids 
{
    IDANY = lex::min_token_id + 10,
    LEFT_PAREN,
    RIGHT_PAREN,
    CHARACTER
};

void build_paren(boost::fusion::vector3<boost::iterator_range<__gnu_cxx::__normal_iterator<char*, std::basic_string<char>>>, char, boost::iterator_range<__gnu_cxx::__normal_iterator<char*, std::basic_string<char>>>> vec)
{
    assert(boost::fusion::at_c<1>(vec) == 'X');
}

char build_character()
{
    return 'X';
}

template <typename Lexer>
struct strip_comments_tokens : lex::lexer<Lexer>
{
    strip_comments_tokens() 
      : strip_comments_tokens::base_type(lex::match_flags::match_default)
    {
        this->self.add
            ('(', LEFT_PAREN)
            (')', RIGHT_PAREN)
            ("-", CHARACTER)
        ;
    }
};

///////////////////////////////////////////////////////////////////////////////
//  Grammar definition
///////////////////////////////////////////////////////////////////////////////
template <typename Iterator>
struct strip_comments_grammar : qi::grammar<Iterator>
{
    template <typename TokenDef>
    strip_comments_grammar(TokenDef const& tok)
      : strip_comments_grammar::base_type(paren)
    {
        paren = (qi::token(LEFT_PAREN) >> character >> qi::token(RIGHT_PAREN)) [ build_paren ]
              ;
        character = qi::token(CHARACTER) [ build_character]
              ;
    }
    
    qi::rule<Iterator> paren;
    qi::rule<Iterator, char()> character;
};

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // iterator type used to expose the underlying input stream
    typedef std::string::iterator base_iterator_type;

    // lexer type
    typedef 
        lex::lexertl::lexer<lex::lexertl::token<base_iterator_type> > 
    lexer_type;

    // iterator type exposed by the lexer 
    typedef strip_comments_tokens<lexer_type>::iterator_type iterator_type;

    // now we use the types defined above to create the lexer and grammar
    // object instances needed to invoke the parsing process
    strip_comments_tokens<lexer_type> strip_comments;           // Our lexer
    strip_comments_grammar<iterator_type> g (strip_comments);   // Our parser 

    // Parsing is done based on the the token stream, not the character 
    // stream read from the input.
    
    std::string str = "(-)";
    base_iterator_type first = str.begin();
    lex::tokenize_and_parse(first, str.end(), strip_comments, g);
    
    return 0;
}