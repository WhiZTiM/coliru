//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
namespace qi  = boost::spirit::qi;

int main() {
    typedef std::string::const_iterator It;
    std::string const line = "<005F> <0061> [<00660066> <00660069> <00660066006C>]";

    It f = line.begin(), l = line.end();

    qi::int_parser<uintmax_t, 16> hex_int;
    qi::rule<It, uintmax_t()> braced_hex = '<' >> hex_int >> '>';
    BOOST_SPIRIT_DEBUG_NODE(braced_hex);

    std::vector<uintmax_t> list;
    bool result = qi::phrase_parse(f, l, *braced_hex >> '[' >> *braced_hex >> ']', qi::space, list);

    if (result) {
        std::cout << "Parse success: " << list.size() << "\n";

        std::copy(list.begin(), list.end(), std::ostream_iterator<uintmax_t>(std::cout, " "));
    }
    else {
        std::cout << "Parse failed\n";
    }

    if (f!=l) {
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
