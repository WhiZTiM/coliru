#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <map>

namespace qi = boost::spirit::qi;

int main() {
    std::cin.unsetf(std::ios::skipws);

    std::map<std::string, int> results;

    if (std::cin >> qi::phrase_match(
                (qi::lexeme[+qi::graph] >> qi::int_parser<int, 16>{}) % qi::eol,
                qi::blank, results)
       )
    {
        std::cout << "Parse success:\n";
        for(auto& entry : results)
            std::cout << "'" << entry.first << "' -> " << entry.second << "\n";
    } else {
        std::cout << "Parse failed\n";
    }
}
