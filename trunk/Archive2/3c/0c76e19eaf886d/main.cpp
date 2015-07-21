#include <iostream>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/adapted.hpp>

namespace qi = ::boost::spirit::qi;

struct strings
{
    std::string a;
    std::string b;
    std::string c;
};

BOOST_FUSION_ADAPT_STRUCT(strings,
  (std::string, a) (std::string, b) (std::string, c))

struct set_field_
{
    void
    operator() (strings& dst, std::string const& src, unsigned& idx) const
    {
        assert (idx <= 2);
        switch (idx++) {
            case 0: dst.a = src; break;
            case 1: dst.b = src; break;
            case 2: dst.c = src; break;
            default: abort ();
        }
    }
};

static boost::phoenix::function<set_field_> const set_field = { set_field_ {} };


template <typename It>
struct split_string_grammar: qi::grammar<It, strings (), qi::locals<unsigned> >
{
    split_string_grammar (unsigned parts)
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
    std::string const input { "one/two/tree/four" };
    
    auto       first = input.begin ();
    auto const last  = input.end ();

    // split into 3 parts.
    split_string_grammar<decltype (first)> split_string (3);
    strings ss;

    bool ok = qi::parse (first, last, split_string, ss);
    
    std::cout << "Parsed: " << ok << "\n";
    
    if (ok) {
        std::cout << "a:" << ss.a << "\n";
        std::cout << "b:" << ss.b << "\n";
        std::cout << "c:" << ss.c << "\n";
    }
}