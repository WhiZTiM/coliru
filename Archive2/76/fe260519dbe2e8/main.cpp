#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct strings {
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

BOOST_FUSION_ADAPT_STRUCT(strings, (std::string, a)(std::string, b)(std::string, c))

template <typename Iterator>
struct google_parser : qi::grammar<Iterator, strings()> {
    google_parser() : google_parser::base_type(entry, "contacts") {
        using namespace qi;

        entry =
                skip('/') [auto_]
              ;
    }
  private:
    qi::rule<Iterator, strings()> entry;
};

int main() {
    using It = std::string::const_iterator;
    google_parser<It> p;

    std::string const input = "part1/part2/part3/also3";
    It f = input.begin(), l = input.end();

    strings ss;
    bool ok = qi::parse(f, l, p >> *qi::char_, ss, ss.c);

    if (ok)
    {
        std::cout << "a:" << ss.a << "\n";
        std::cout << "b:" << ss.b << "\n";
        std::cout << "c:" << ss.c << "\n";
    }
    else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
