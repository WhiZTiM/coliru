#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/algorithm/iteration.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace fus = boost::fusion;

struct strings {
    std::string a, b, c;
};

BOOST_FUSION_ADAPT_STRUCT(strings, a, b, c)

struct set_field_
{
    struct Foo {
        unsigned           target_idx;
        std::string const& value;

        template <typename B>
        unsigned operator()(unsigned i, B& dest) const {
            if (target_idx == i) dest = value;
            return i + 1;
        }
    };

    template <typename Seq>
    void operator() (Seq& seq, std::string const& src, unsigned idx) const {
        fus::fold(seq, 0u, Foo { idx, src });

        fus::fold(seq, 0u, [&](unsigned current, auto& dest) mutable {
                    if (idx == current) dest = src;
                    return current + 1;
                });
    }
};

boost::phoenix::function<set_field_> const set_field = {};

template <typename It>
struct split_string_grammar: qi::grammar<It, strings (), qi::locals<unsigned> >
{
    split_string_grammar (int parts)
        : split_string_grammar::base_type (split_string)
    {
        assert (parts > 0);

        using namespace qi;
        using boost::phoenix::val;

        split_string = eps [ _a = val (0) ]
            > repeat (parts-1) [part [ set_field (_val, _1, _a) ] > '/']
            > last_part [ set_field (_val, _1, _a) ];

        part = +(~char_ ("/"));
        last_part = +char_;

        BOOST_SPIRIT_DEBUG_NODES ((split_string) (part) (last_part))
    }

private:
    qi::rule<It, strings (), qi::locals<unsigned> > split_string;
    qi::rule<It, std::string ()> part, last_part;
};

int main ()
{
    std::string const input { "one/two/three/four" };

    auto const last  = input.end ();
    auto       first = input.begin ();

    // split into 3 parts.
    split_string_grammar<decltype (first)> split_string (3);
    strings ss;

    bool ok = qi::parse (first, last, split_string, ss);

    std::cout << "Parsed: " << ok << "\n";

    if (ok) {
        std::cout << boost::fusion::as_vector(ss) << '\n';
    }
}
