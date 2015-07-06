#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main() {
    std::string const line = "%%DocumentNeededResources: CMap (90pv-RKSJ-UCS2C)";

    auto first = line.begin(), last = line.end();

    std::string label, token;
    bool ok = qi::phrase_parse(
            first, last, 
            qi::lexeme [ "%%" >> +~qi::char_(":") ] >> ':' >> qi::lexeme["CMap"] >> '(' >> qi::lexeme[+~qi::char_(')')] >> ')',
            qi::space,
            label, token);

    if (ok)
        std::cout << "Parse success: label='" << label << "', token='" << token << "'\n";
    else
        std::cout << "Parse failed\n";

    if (first!=last)
        std::cout << "Remaining unparsed input: '" << std::string(first, last) << "'\n";
}
