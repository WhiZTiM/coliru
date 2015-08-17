#include <boost/spirit/include/qi.hpp>
#include <iostream>


template <typename P, typename T>
void test_parser_attr(
    char const* input, P const& p, T& attr, bool full_match = true)
{
    using boost::spirit::qi::parse;

    char const* f(input);
    char const* l(f + strlen(f));
    if (parse(f, l, p, attr) && (!full_match || (f == l)))
        std::cout << "ok" << std::endl;
    else
        std::cout << "fail" << std::endl;
}

int main()
{
    using boost::spirit::qi::auto_;
    short s;
    int i;
    test_parser_attr("-2147483648", auto_, i);
    test_parser_attr("-2147483648", auto_, s);
}
