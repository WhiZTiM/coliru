#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main() {
    typedef std::string::const_iterator It;

    qi::rule<It, std::string()> escaped_ = '"' >> *(qi::char_ - '"') >> '"';

    std::string const input("0  \"a\"  \"b\"  \"c\"\n");
    It begin(input.begin()), end(input.end());

    int id;
    std::string v1,v2,v3;

    bool ok = qi::phrase_parse(begin, end, (qi::int_ >> escaped_ >> escaped_ >> escaped_ >> qi::eol), qi::blank, id, v1, v2, v3);

    if (ok) {
        std::cout << "Parse succeeded:" 
                  << " "  << id
                  << " '" << v1 << "'"
                  << " '" << v2 << "'"
                  << " '" << v3 << "'\n";
    } else {
        std::cout << "Parse failed\n";
    }

    if (begin != end)
        std::cout << "Remaining unparsed '" << std::string(begin, end) << "'\n";
   
}
