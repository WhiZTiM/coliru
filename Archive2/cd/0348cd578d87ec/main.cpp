#include <boost/spirit/include/qi.hpp>

int main() {
    namespace qi  = boost::spirit::qi;

    std::string const strLinesRecur = "%%DocumentNeededResources: CMap (90pv-RKSJ-UCS2C)";

    auto code    = qi::copy(qi::raw [ +(qi::alnum | qi::char_('-')) ]);
    auto grammar = qi::copy(
            qi::omit [ "%%" >> +qi::alpha >> ':' >> +qi::alpha ]
            >> '(' >> code >> ')');

    std::string res;
    if (qi::phrase_parse(begin(strLinesRecur), end(strLinesRecur), grammar, qi::blank, res))
        std::cout << "Result: " << res << std::endl;
    else
        std::cout << "Parse did not succeed\n";
}
