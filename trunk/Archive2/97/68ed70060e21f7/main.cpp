//#define BOOST_SPIRIT_DEBUG
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
                qi::lexeme [+(qi::char_ - ',' - qi::eol)] | qi::attr("(unspecified)")
            )
        >::type type;

        static type call() {
            return proto::deep_copy(
                qi::lexeme [+(qi::char_ - ',' - qi::eol)] | qi::attr("(unspecified)")
            );
        }
    };
}}}

BOOST_FUSION_ADAPT_STRUCT(data, (std::string, a)(std::string, b)(std::string, c))

template <typename Iterator, typename skipper = qi::blank_type>
struct google_parser : qi::grammar<Iterator, data(), skipper> {
    google_parser() : google_parser::base_type(entry, "contacts") {
        using namespace qi;

        entry = skip(skipper() | ',') [auto_] >> eol;

        BOOST_SPIRIT_DEBUG_NODES((value)(entry))
    }
  private:
    qi::rule<Iterator, data(), skipper> entry;
};

int main() {
    using It = std::string::const_iterator;
    google_parser<It> p;

    for (std::string input : { 
            "something, awful, is\n",
            "fine,,just\n",
            "like something missing: ,,\n",
        })
    {
        It f = input.begin(), l = input.end();

        data parsed;
        bool ok = qi::phrase_parse(f,l,p,qi::blank,parsed);

        if (ok)
            std::cout << "Parsed: '" << parsed.a << "', '" << parsed.b << "', '" << parsed.c << "'\n";
        else
            std::cout << "Parse failed\n";

        if (f!=l)
            std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}