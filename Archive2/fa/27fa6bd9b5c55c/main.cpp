#include <boost/spirit/include/qi.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;

int main() {
    std::ifstream ifs("input.txt");

    //In header in my code
    std::vector<unsigned long long> v_BF_Char;

    static qi::uint_parser<uint64_t, 16, 4, 16> hex_int;

    typedef boost::spirit::istream_iterator It;
    It begin(ifs >> std::noskipws), end;

    // rule for grammer
    static const qi::rule<It, std::vector<uint64_t>()> braced_hex 
        = '<' >> qi::repeat(1,2)[hex_int] >> '>';

    bool ok = qi::phrase_parse(begin, end, *braced_hex, qi::space, v_BF_Char);

    if (ok)
        std::cout << "Parsed: " << v_BF_Char.size() << " elements\n";
    else
        std::cout << "Parsing failed\n";

    if (begin!=end)
        std::cout << "Remaining input unparsed: '" << std::string(begin, end) << "'\n";
}
