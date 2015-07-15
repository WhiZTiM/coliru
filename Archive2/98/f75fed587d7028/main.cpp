#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>

namespace qi      = boost::spirit::qi;
namespace phoenix = boost::phoenix;

struct data_t {
    std::string module, command;
};

BOOST_FUSION_ADAPT_STRUCT(data_t, (std::string,module)(std::string,command))

template <typename Iterator, typename Skipper = qi::blank_type>
struct myCommandParser : public qi::grammar<Iterator, data_t(), Skipper>
{
    myCommandParser() : myCommandParser::base_type(start)
    {
        using namespace qi;
        start %=
               lexeme[+~char_(' ')]
            >> lexeme[+~char_('\n')]
            ;
    };

    qi::rule<Iterator, data_t(), Skipper> start;
};

int main()
{
    myCommandParser<std::string::const_iterator> commandGrammar;

    data_t our_data;
    std::cout << "Module name before parsing: " << our_data.module << std::endl;

    std::string const str("mod01 cmd02\n");
    std::string::const_iterator f(str.begin()), l(str.end());
    qi::phrase_parse(f, l, commandGrammar, qi::blank, our_data);

    std::cout << "Module name after parsing: " << our_data.module  << std::endl;
    std::cout << "Command after parsing:     " << our_data.command << std::endl;
}
