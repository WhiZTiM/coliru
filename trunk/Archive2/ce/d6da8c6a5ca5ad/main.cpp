#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct data {
    std::string a;
    std::string b;
    std::string c;
};

namespace boost { namespace spirit { namespace traits {
    template <> struct create_parser<std::string> {
        typedef proto::result_of::deep_copy<
            BOOST_TYPEOF(
                qi::lexeme [+(qi::char_ - '/')] | qi::attr("(unspecified)")
            )
        >::type type;

        static type call() {
            return proto::deep_copy(
                qi::lexeme [+(qi::char_ - '/')] | qi::attr("(unspecified)")
            );
        }
    };
}}}

BOOST_FUSION_ADAPT_STRUCT(data, (std::string, a)(std::string, b)(std::string, c))

template <typename Iterator>
struct google_parser : qi::grammar<Iterator, data()> {
    google_parser() : google_parser::base_type(entry, "contacts") {
        using namespace qi;

        entry =
                skip('/') [auto_]
              ;
    }
  private:
    qi::rule<Iterator, data()> entry;
};

int main() {
    using It = std::string::const_iterator;
    google_parser<It> p;

    std::string const input = "part1/part2/part3/also3";
    It f = input.begin(), l = input.end();

    data parsed;
    bool ok = qi::parse(f, l, p >> *qi::char_, parsed, parsed.c);

    if (ok)
    {
        std::cout << "a:" << parsed.a << "\n";
        std::cout << "b:" << parsed.b << "\n";
        std::cout << "c:" << parsed.c << "\n";
    }
    else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
