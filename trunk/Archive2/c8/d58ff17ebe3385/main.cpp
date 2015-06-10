#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
namespace qi = boost::spirit::qi;

int main() {
    std::vector<std::vector<std::string>> csv_data;

    if (std::cin 
            >> std::noskipws 
            >> qi::phrase_match(*qi::lexeme['"' >> *('\\' >> qi::char_ | ~qi::char_("\r\n\"")) >> '"'] % qi::eol, qi::blank, csv_data))
    {
        std::cout << "Parse succeeded: " << csv_data.size() << "\n";
        for(auto& row: csv_data) {
            for(auto& c: row) std::cout << c << '|';
            std::cout << "\n";
        }
    } else {
        std::cout << "Parse failed\n";
    }
}
