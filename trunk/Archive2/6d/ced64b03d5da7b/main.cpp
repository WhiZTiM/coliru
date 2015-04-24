#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <iostream>
namespace qi = boost::spirit::qi;

int main() {
    std::vector<double> values;
    std::cin >> std::noskipws >> qi::phrase_match(*('"'>*qi::double_>'"'), qi::space, values);

    for (auto d : values)
        std::cout << d << "\n";
}
