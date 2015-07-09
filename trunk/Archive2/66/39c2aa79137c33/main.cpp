#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename It, typename Skipper> 
struct Parser : qi::grammar<It, std::string(), Skipper> {
    Parser() : Parser::base_type(start)  {
        using namespace qi;

        a_symbol      += "aap", "noot", "mies";
        start          = raw [ no_case [ a_symbol >> "literal" >> char_("qwerty") >> -subrule_lexeme ] ];
        start          = raw [ no_case [ a_symbol >> "literal" >> char_("qwerty") >> -subrule_lexeme ] ];
        subrule_lexeme = "also works";

        BOOST_SPIRIT_DEBUG_NODES((start)(subrule_lexeme))
    }
  private:
    qi::symbols<char, qi::unused_type> a_symbol;
    qi::rule<It, std::string(), Skipper> start;
    qi::rule<It, std::string()> subrule_lexeme;
};

// test
using It = std::string::const_iterator;

template <typename S = qi::space_type> void test(S const& s = S()) {
    Parser<It, S> g;

    for (std::string const& input : { 
            "aap\t literal r",
            "aAp\t liTeral R",
            // hitting subrule_lexeme:
            "aap\t literal r\talso works",
            "aAp\t liTeral R\tALSO WoRkS",
        })
    {
        It f = input.begin(), l = input.end();

        std::string parsed;
        bool ok = qi::phrase_parse(f, l, g, s, parsed);

        if (ok)
            std::cout << "Parsed successfully: '" << parsed << "'\n";
        else
            std::cout << "Not matched ('" << input << "')\n";

        if (f!=l)
            std::cout << " -- remaining unparsed input: '" << std::string(f,l) << "'\n";
    }
}

int main()
{
    test(qi::space);
}
