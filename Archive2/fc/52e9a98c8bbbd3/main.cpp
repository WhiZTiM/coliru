#define BOOST_SPIRIT_USE_PHOENIX_V3 1
#define BOOST_SPIRIT_DEBUG 1

#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <iostream>
#include <string>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator, typename Skipper = ascii::space_type>
struct SystemParser : qi::grammar<Iterator, std::vector<std::string>(), Skipper> {

    SystemParser() : SystemParser::base_type(variable_group_) 
    {
        declarative_symbols += "variable_group";

        variable_group_        = "variable_group" >> genericvargp_ >> ';';
        genericvargp_          = new_variable_ % ',';
        valid_variable_name_   = qi::alpha >> *(qi::alnum | qi::char_("_[]"));
        unencountered_symbol_  = valid_variable_name_ - (encountered_variables|declarative_symbols);
        new_variable_          = unencountered_symbol_;

        BOOST_SPIRIT_DEBUG_NODES((variable_group_) (valid_variable_name_) (unencountered_symbol_) (new_variable_) (genericvargp_))
    }
  private:

    qi::symbols<char, qi::unused_type> encountered_variables, declarative_symbols;

    // rule declarations.  these are member variables for the parser.
    qi::rule<Iterator, std::vector<std::string>(), Skipper> variable_group_;
    qi::rule<Iterator, std::vector<std::string>(), Skipper> genericvargp_;
    qi::rule<Iterator, std::string()> new_variable_;
    qi::rule<Iterator, std::string()> unencountered_symbol_; // , Skipper

    // the rule which determines valid variable names
    qi::rule<Iterator, std::string()> valid_variable_name_;
};

//#include "system_parsing.hpp"

int main() {

    using It = std::string::const_iterator;
    std::string const str = "variable_group x, y, z;";

    SystemParser<It> S;

    It iter = str.begin(), end = str.end();
    std::vector<std::string> V;
    bool s = phrase_parse(iter, end, S, boost::spirit::ascii::space, V);

    if (s)
    {
        std::cout << "Parse succeeded: " << V.size() << "\n";
        for (auto& s : V)
            std::cout << " - '" << s << "'\n";
    }
    else
        std::cout << "Parse failed\n";

    if (iter!=end)
        std::cout << "Remaining unparsed: '" << std::string(iter, end) << "'\n";
}
