#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/lexical_cast.hpp>
using namespace boost::spirit;

template <typename Iterator>
struct demo : qi::grammar<Iterator, std::string(), ascii::space_type> {
    demo() : demo::base_type(text) {
        text = qi::raw [ qi::int_ ];
    }

    qi::rule<Iterator, std::string(), ascii::space_type> text;
};

int main()
{
    using It = std::string::const_iterator;
    std::string const test("3");

    It beg = test.begin(), end = test.end();
    demo<std::string::const_iterator> par;

    std::string result;
    if (qi::phrase_parse(beg, end, par, qi::space, result))
        std::cout << "Result is " << boost::lexical_cast<std::string>(result) << std::endl;
}
