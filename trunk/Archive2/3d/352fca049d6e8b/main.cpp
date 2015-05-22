#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <cmath>
#include <iostream>

int main ()
{
    using It = std::string::const_iterator;

    auto my_fpnumber = [] { // TODO encapsulate in a grammar struct
        using namespace boost::spirit::qi;
        using boost::phoenix::size;

        static boost::phoenix::function<decltype(&::isnan)> isnan_(&::isnan);

        return rule<It, double()> (
                raw [ double_ [_val = _1] ] [ _pass = !isnan_(_val) && size(_1)<=4 ]
            );
    }();

    for (std::string const s: { "1.23", ".123", "2.e6", "inf", "3.2323", "nan" })
    {
        It f = s.begin(), l = s.end();

        double result;
        if (parse(f, l, my_fpnumber, result))
            std::cout << "Parse success:  '" << s << "' -> " << result << "\n";
        else
            std::cout << "Parse rejected: '" << s << "' at '" << std::string(f,l) << "'\n";
    }
}
