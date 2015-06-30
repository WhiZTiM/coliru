#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename Iterator, typename Skipper = qi::ascii::space_type>
struct Grammar : qi::grammar<Iterator, Skipper> {
    Grammar() : Grammar::base_type(expression) { }
private:
    qi::rule<Iterator, Skipper> const
        // Tokens
        scalar_literal { qi::uint_ | qi::int_ },
        identifier     { qi::lexeme[(qi::alpha | '_') >> *(qi::alnum | '_')] },
        // Rules
        operand        { (scalar_literal | identifier | ('(' >> expression >> ')')) },
        expression     { operand };
};

int main() {
    using It = std::string::const_iterator;
    Grammar<It> p;
    std::string const input = "(123)";

    It f = input.begin(), l = input.end();

    bool ok = qi::phrase_parse(f,l,p,qi::ascii::space);

    if (ok)   std::cout << "Parse success\n";
    else      std::cout << "Parse failed\n";
    if (f!=l) std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}