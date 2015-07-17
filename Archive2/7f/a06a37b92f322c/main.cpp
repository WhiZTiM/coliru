
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/phoenix.hpp>

#include <iostream>
#include <string>

namespace qi  = boost::spirit::qi;
namespace phoenix = boost::phoenix;


class moduleAccessManager
{
public:
    bool getModule(const std::string name)
	{
		if(name == "cat" || name == "dog")
			return true;
		else
			return false;
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
    	module	=	qi::as_string[qi::lexeme[+(~qi::char_(' '))]]
    		[&globalIsModule] // This works fine
//    		[phoenix::bind(&moduleCommandParser::isModule, this)] // Compile error
			;
		start	 =	module >> qi::as_string[+(~qi::char_('\n'))];
    };

	void isModule(std::string moduleName, const boost::spirit::unused_type&, bool& mFlag)
	{
		// Check if a module with moduleName exists
		if(m_acm->getModule(moduleName))
			std::cout << "[isModule] Info: Found module with name >"  << moduleName << "<" << std::endl;
		else
		{
			std::cout << "[isModule] Error: No module with name >" << moduleName << "<" << std::endl;
			mFlag = false; // No valid module name
		}
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
	qi::phrase_parse(first, last, commandGrammar, qi::space);

	str = "bird fly";
	first = str.begin();
	last = str.end();
	qi::phrase_parse(first, last, commandGrammar, qi::space);
}
