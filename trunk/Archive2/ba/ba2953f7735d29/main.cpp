#include <boost/spirit/include/qi.hpp>
namespace qi  = boost::spirit::qi;

namespace /*static*/ {
    static auto code    = qi::copy(qi::raw [ +(qi::alnum | '-') ]);
    static auto grammar = qi::copy(
            qi::omit [ "%%" >> +qi::alpha >> ':' >> +qi::alpha ]
            >> '(' >> code >> ')'
        );
}

int main() {
    std::string const input = "%%DocumentNeededResources: CMap (90pv-RKSJ-UCS2C)";
    std::string res;

    if (qi::phrase_parse(begin(input), end(input), grammar, qi::blank, res))
        std::cout << "Result: " << res << std::endl;
    else
        std::cout << "Parse did not succeed\n";
}
