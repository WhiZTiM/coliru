#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

typedef boost::variant<int, double, std::string> value_t;
typedef std::map<std::string, value_t> namevalue;
typedef std::pair<std::string, value_t> namevaluepair;

template <typename Iterator>
struct keys_and_values2
    :   qi::grammar<Iterator, namevalue(), ascii::blank_type>
{
    keys_and_values2() : keys_and_values2::base_type(start)
    {
        start %= query >> qi::eoi;
        query =  +pair;
        value =  strict_double | qi::int_ | qi::lexeme[+(qi::char_ - qi::eol)] ;
        pair  =  key >> qi::lit(':') >> value >> qi::eol;
        key   =  qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z_0-9");

        BOOST_SPIRIT_DEBUG_NODES((start)(query)(value)(pair)(key))
    }
  private:
    qi::real_parser<double, qi::strict_real_policies<double> > strict_double;
    qi::rule<Iterator, namevalue(),     ascii::blank_type> start;
    qi::rule<Iterator, namevalue(),     ascii::blank_type> query;
    qi::rule<Iterator, namevaluepair(), ascii::blank_type> pair;
    qi::rule<Iterator, std::string(),   ascii::blank_type> key;
    qi::rule<Iterator, value_t(),       ascii::blank_type> value;
};

int main() {
    typedef boost::spirit::istream_iterator It;
    It f(std::cin >> std::noskipws), l;

    keys_and_values2<It> g;
    namevalue data;
    bool ok = qi::phrase_parse(f,l,g,ascii::blank,data);

    if (ok) {
        std::cout << "Parse succeeded:\n";
        for(auto& p : data)
            std::cout << "\t'" << p.first << "'\t-> " << p.second << "\n";
    } else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
