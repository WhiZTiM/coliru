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

struct alternative {
    std::vector<char> first;
    std::string       second;
    std::string       third;
};

BOOST_FUSION_ADAPT_STRUCT(strings, a, b, c)
BOOST_FUSION_ADAPT_STRUCT(alternative, third, second, first) // REVERSE ORDER :)

// output helpers for demo:
namespace {
    inline std::ostream& operator<<(std::ostream& os, strings const& data) {
        return os 
            << "a:\"" << data.a << "\" " 
            << "b:\"" << data.b << "\" " 
            << "c:\"" << data.c << "\" ";
    }

    inline std::ostream& operator<<(std::ostream& os, alternative const& data) {
        os << "first: vector<char> { \""; os.write(&data.first[0], data.first.size()); os << "\" } ";
        os << "second: \"" << data.second << "\" ";
        os << "third: \""  << data.third  << "\" ";
        return os;
    }
}

struct set_field_
{
    template <typename Seq, typename Value>
    void operator() (Seq& seq, Value const& src, unsigned idx) const {
        fus::fold(seq, 0u, Visit<Value> { idx, src });
    }
  private:
    template <typename Value>
    struct Visit {
        unsigned     target_idx;
        Value const& value;

        template <typename B>
        unsigned operator()(unsigned i, B& dest) const {
            if (target_idx == i) {
                boost::spirit::traits::assign_to(value, dest);
            }
            return i + 1;
        }
    };
};

boost::phoenix::function<set_field_> const set_field = {};

template <typename It, typename Target>
struct split_string_grammar: qi::grammar<It, Target(), qi::locals<unsigned> >
{
    split_string_grammar (int parts)
        : split_string_grammar::base_type (split_string)
    {
        assert (parts > 0);

        using namespace qi;
        using boost::phoenix::val;

        _a_type _current; // custom placeholder

        split_string = 
              eps       [ _current = 0u ]
            > repeat (parts-1) 
                [part   [ set_field(_val, _1, _current++) ] > '/']
            > last_part [ set_field(_val, _1, _current++) ];

        part = +(~char_ ("/"));
        last_part = +char_;

        BOOST_SPIRIT_DEBUG_NODES ((split_string) (part) (last_part))
    }

private:
    qi::rule<It, Target(), qi::locals<unsigned> > split_string;
    qi::rule<It, std::string()> part, last_part;
};

template <size_t N = 3, typename Target>
void run_test(Target target) {
    using It = std::string::const_iterator;
    std::string const input { "one/two/three/four" };

    It first = input.begin(), last = input.end();

    split_string_grammar<It, Target> split_string(N);

    bool ok = qi::parse (first, last, split_string, target);

    if (ok) {
        std::cout << target << '\n';
    } else {
        std::cout << "Parse failed\n";
    }

    if (first != last)
        std::cout << "Remaining input left unparsed: '" << std::string(first, last) << "'\n";
}

int main ()
{
    run_test(strings {});
    run_test(alternative {});
}
