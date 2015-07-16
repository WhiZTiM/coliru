/*!
 * \file main.cpp
 * \brief Kurzbeschreibung
 * \ingroup Modulname
 * \author kobe
 * \date 14.07.2015 (Datei angelegt)
 * \note Encoding: UTF-8
 * \copyright EK-TEAM GmbH
 */


#include <boost/bind.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace qi  = boost::spirit::qi;
namespace phoenix = boost::phoenix;

typedef std::pair<std::string, std::string> stringPair_t;

struct bla {
    std::string module, command;
};

BOOST_FUSION_ADAPT_STRUCT(bla, (std::string,module)(std::string,command))


void printParameters(const std::string & module, const std::string & command)
{
	std::cout << "Module name during parse: " << module << std::endl;
    std::cout << "Command name during parse: " << command << std::endl;

}


template <typename Iterator, typename Skipper>
struct myCommandParser : public qi::grammar<Iterator, bla(), Skipper>
{
    myCommandParser() : myCommandParser::base_type(start)
    {
		start %=
				qi::lexeme[+(~qi::char_(' '))] [phoenix::ref(m_moduleName) = qi::_1]
			 >> qi::lexeme[+(~qi::char_('\n'))] //[phoenix::bind(&printParameters, /*"Hello, "*/phoenix::cref(m_moduleName), "world!"/*qi::_1*/)]
			 	;
    };

   	qi::rule<Iterator, bla(), Skipper> start;
    std::string m_moduleName;
};


int main()
{
    myCommandParser<std::string::const_iterator, qi::space_type> commandGrammar;

    commandGrammar.m_moduleName = std::string("initial_default");
    std::cout << "Module name before parsing: " << commandGrammar.m_moduleName << std::endl;

	bla ourData;

	std::string str("mod01 cmd02\n");
    std::string::const_iterator first = str.begin();
    std::string::const_iterator last = str.end();
    bool r = qi::phrase_parse(first, last, commandGrammar, qi::space, ourData);
    if(r == false)
    	std::cout << "Parsing failed" << std::endl;

    std::cout << "Module name after parsing: " << ourData.module << std::endl;
    std::cout << "Module command after parsing: " << ourData.command << std::endl;
}
