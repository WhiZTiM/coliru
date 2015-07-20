#include <iostream>

#include <boost/spirit/include/qi.hpp>
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

template <typename It>
struct split_string_grammar: qi::grammar<It, strings ()>
{
    split_string_grammar (int parts)
        : split_string_grammar::base_type (split_string)
    {
        assert (parts > 0);
        
        using namespace qi;
        
        split_string = repeat (parts-1) [no_skip[part] > '/'] > last_part;
        
        part = +(~char_ ("/"));
        last_part = +char_;

        BOOST_SPIRIT_DEBUG_NODES ((split_string) (part) (last_part))
    }

private:
    qi::rule<It, strings ()> split_string;
    qi::rule<It, std::string ()> part, last_part;
};

int main ()
{
    std::string const input { "one/two/tree/four" };
    
    auto const last  = input.end ();
    auto       first = input.begin ();

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