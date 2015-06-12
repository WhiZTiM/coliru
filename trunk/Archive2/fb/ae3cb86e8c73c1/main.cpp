#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/lexical_cast.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    using It = std::string::const_iterator;
    std::string const test("3");

    It beg = test.begin(), end = test.end();
    demo<std::string::const_iterator> par;

    int result;
    if (qi::phrase_parse(beg, end, qi::int_, qi::space, result))
        std::cout << "Result is " << boost::lexical_cast<std::string>(result) << std::endl;
}
