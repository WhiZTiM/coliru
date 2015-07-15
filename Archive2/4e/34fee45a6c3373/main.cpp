#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>

namespace qi      = boost::spirit::qi;
namespace phoenix = boost::phoenix;

struct data_t {
    std::string module, command;
};

BOOST_FUSION_ADAPT_STRUCT(data_t, (std::string,module)(std::string,command))

template <typename Iterator>
struct myCommandParser : public qi::grammar<Iterator, data_t()>
{
    myCommandParser() : myCommandParser::base_type(start)
    {
        start %=
               +(~qi::char_(' ')) 
            >> ' '
            >> +(~qi::char_('\n'))

            //[ phoenix::ref(std::cout) << "Module name during parse: " << qi::_1 << "\nCommand name during parse: " << qi::_2 << "\n" ]
            ;
    };

    qi::rule<Iterator, data_t()> start;
};

int main()
{
    myCommandParser<std::string::const_iterator> commandGrammar;

    data_t our_data;
    std::cout << "Module name before parsing: " << our_data.module << std::endl;

    std::string const str("mod01 cmd02\n");
    qi::parse(str.begin(), str.end(), commandGrammar, our_data);

    std::cout << "Module name after parsing: " << our_data.module  << std::endl;
    std::cout << "Command after parsing:     " << our_data.command << std::endl;
}
