#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    std::string const str("mod01 cmd02\n");
    std::string moduleName, command;
    qi::parse(str.begin(), str.end(), +~qi::char_(' ') >> +~qi::char_('\n'), moduleName, command);  

    std::cout << "Module name after parsing: " << moduleName << "\n";
    std::cout << "Command after parsing:     " << command    << "\n";
}
