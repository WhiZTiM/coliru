#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <iostream>
#include <string>

namespace qi      = boost::spirit::qi;
namespace phoenix = boost::phoenix;

class moduleAccessManager {
public:
    bool getModule(const std::string name) {
        return name == "cat" || name == "dog";
    }
};

void globalIsModule(std::string moduleName, const boost::spirit::unused_type&, bool& mFlag)
{
        moduleAccessManager acm; /* Dirty workaround for this example */
        if(acm.getModule(moduleName))
            std::cout << "[isModule] Info: Found module with name >"  << moduleName << "<" << std::endl;
        else
        {
            std::cout << "[isModule] Error: No module with name >" << moduleName << "<" << std::endl;
            mFlag = false; // No valid module name
        }
}

template <typename Iterator, typename Skipper>
class moduleCommandParser : public qi::grammar<Iterator, Skipper>
{
private:
    moduleAccessManager* m_acm;

    qi::rule<Iterator, Skipper> start, module;

public:
    std::string m_moduleName;

    moduleCommandParser(moduleAccessManager* acm)
        : moduleCommandParser::base_type(start)
        , m_acm(acm)
        , m_moduleName("<empty>")
    {
        using namespace phoenix::arg_names;
        module  =   qi::as_string[qi::lexeme[+(~qi::char_(' '))]]
                        [qi::_pass = phoenix::bind(&moduleAccessManager::getModule, m_acm, qi::_1)]
                    ;
        start   =  module >> qi::as_string[+(~qi::char_('\n'))];
    };

};


int main()
{
    moduleAccessManager acm;
    moduleCommandParser<std::string::const_iterator, qi::space_type> commandGrammar(&acm);

    std::string str;
    std::string::const_iterator first;
    std::string::const_iterator last;

    str = "cat run";
    first = str.begin();
    last = str.end();
    std::cout << str << std::boolalpha 
              << qi::phrase_parse(first, last, commandGrammar, qi::space);

    str = "bird fly";
    first = str.begin();
    last = str.end();
    std::cout << str << std::boolalpha 
              << qi::phrase_parse(first, last, commandGrammar, qi::space);
}
