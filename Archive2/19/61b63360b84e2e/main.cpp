#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phoenix = boost::phoenix;

void printParameters(const std::string & module, const std::string & command)
{
    std::cout << "Module name during parse: " << module << std::endl;
    std::cout << "Command name during parse: " << command << std::endl;
}

template <typename Iterator>
struct myCommandParser : public qi::grammar<Iterator>
{
    myCommandParser() : myCommandParser::base_type(start)
    {
        start = 
                qi::as_string[+(~qi::char_(' '))] [ phoenix::ref(m_moduleName) = qi::_1 ]
             >> qi::as_string[+(~qi::char_('\n'))][ phoenix::bind(&printParameters, phoenix::cref(m_moduleName), qi::_1) ];
    };

    qi::rule<Iterator> start;
    std::string m_moduleName;
};


int main()
{
    myCommandParser<std::string::const_iterator> commandGrammar;

    commandGrammar.m_moduleName = std::string("initial_default");
    std::cout << "Module name before parsing: " << commandGrammar.m_moduleName << std::endl;

    std::string str("mod01 cmd02\n");
    std::string::const_iterator first = str.begin();
    std::string::const_iterator last = str.end();
    qi::parse(first, last, commandGrammar);

    std::cout << "Module name after parsing: " << commandGrammar.m_moduleName << std::endl;
}
