#include <boost/spirit/include/qi.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;

int main() {
    std::ifstream ifs("input.txt");

    //In header in my code
    std::vector<unsigned long long> v_BF_Char;

    //qi::int_parser<uintmax_t, 16> hex_int;
    static qi::uint_parser<uint64_t, 16, 16, 16> hex_int;

    std::string line;
    while (std::getline(ifs, line))
    {
        typedef std::string::const_iterator It;
        It begin = line.begin(), end = line.end();

        // rule for grammer
        qi::rule<It, std::vector<uint64_t>()> braced_hex = '<' >> qi::repeat(1,2)[hex_int] >> '>';

        bool ok = qi::phrase_parse(begin, end, *braced_hex,  qi::space, v_BF_Char);
    }
}
