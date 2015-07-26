#include <boost/spirit/include/qi.hpp>

namespace qi  = boost::spirit::qi;


int main() 
{
    std::string const input( "Hello World" );

    {
        typedef qi::rule<std::string::const_iterator, std::string()> rule_type;
        rule_type value_rule = +qi::char_ - ( '[' | qi::eoi );

        std::string value;
        bool ok = qi::parse( input.begin( ),
                input.end( ),
                value_rule,
                value );

        std::cout << std::boolalpha << ok << "\t" << value << "\n";
    }

    {
        std::string value;
        bool ok = qi::parse( input.begin( ),
                input.end( ),
                +qi::char_ - ( '[' | qi::eoi ),
                value );

        std::cout << std::boolalpha << ok << "\t" << value << "\n";
    }
}

