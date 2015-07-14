#include <string>
#include <cstring>
#include <boost/spirit/include/lex.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace lex        = boost::spirit::lex;
namespace qi         = boost::spirit::qi;
namespace phoenix    = boost::phoenix;

std::string regex("FOO\\/BAR");

template <typename Type>
struct Lexer : boost::spirit::lex::lexer<Type> {
    Lexer() : foobar_(regex),white_space("[ \\t\\n]+") {
        this->self.add(foobar_);
        this->self("WS") = white_space;
    }
    boost::spirit::lex::token_def<std::string> foobar_;
    boost::spirit::lex::token_def<lex::omit> white_space;
};

template <typename Iterator, typename Def>
struct Grammar
  : qi::grammar <Iterator, qi::in_state_skipper<Def> > {
    template <typename Lexer> Grammar(const Lexer & _lexer);
    typedef qi::in_state_skipper<Def> Skipper;
    qi::rule<Iterator, Skipper> rule_;
};
template <typename Iterator, typename Def>
template <typename Lexer>
Grammar<Iterator, Def>::Grammar(const Lexer & _lexer)
  : Grammar::base_type(rule_) {
    rule_ = _lexer.foobar_;
}

int main() {
    // INPUT
    char const * first("FOO/BAR");
    char const * last(first + strlen(first));

    // LEXER
    typedef lex::lexertl::token<const char *> Token;
    typedef lex::lexertl::lexer<Token> Type;
    Lexer<Type> l;

    // GRAMMAR
    typedef Lexer<Type>::iterator_type Iterator;
    typedef Lexer<Type>::lexer_def Def;
    Grammar<Iterator, Def> g(l);

    // PARSE
    bool ok = lex::tokenize_and_phrase_parse (
        first
      , last
      , l
      , g
      , qi::in_state("WS")[l.self]
    );

    // CHECK
    if (!ok || first != last) {
        std::cout << "Failed parsing input file" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Everything went well" << std::endl;
    }
    return 0;
}
