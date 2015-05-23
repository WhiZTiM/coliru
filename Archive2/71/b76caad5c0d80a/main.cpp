//#define BOOST_SPIRIT_DEBUG
#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <iostream>
#include <string>
#include <map>

namespace ast {
    typedef boost::make_recursive_variant<std::string, std::map<std::string, boost::recursive_variant_> >::type Value;
    typedef std::map<std::string, Value> Sequence;
}

namespace qi = boost::spirit::qi;

template <typename It, typename Skipper>
struct NestedGrammar : qi::grammar <It, ast::Sequence(), Skipper>
{
    NestedGrammar() : NestedGrammar::base_type(Sequence)
    {
        using namespace qi;
        KeyName = qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z0-9_");
        String = +qi::char_("-.a-zA-Z_0-9");

        Pair = KeyName >> -(
                '=' >> ('{' >> Sequence >> '}' | String)
            );

        Sequence = Pair % char_(";&") >> -omit[char_(";&")];

        BOOST_SPIRIT_DEBUG_NODES((KeyName) (String) (Pair) (Sequence))
    }
private:
    qi::rule<It, ast::Sequence(),                      Skipper> Sequence;
    qi::rule<It, std::pair<std::string, ast::Value>(), Skipper> Pair;
    qi::rule<It, std::string(),                        Skipper> String;
    qi::rule<It, std::string()>                                 KeyName;
};


template <typename Iterator>
ast::Sequence Parse2(Iterator begin, Iterator end)
{
    NestedGrammar<Iterator, qi::space_type> p;
    ast::Sequence data;
    qi::phrase_parse(begin, end, p, qi::space, data);
    return data;
}

void NestedParse(std::string Input, ast::Sequence& Output)
{
    //Input.erase(std::remove_if(Input.begin(), Input.end(), isspace), Input.end());
    Output = Parse2(Input.begin(), Input.end());
}

static inline std::ostream& operator<<(std::ostream& os, ast::Value const& value) {
    struct vis : boost::static_visitor<> {
        vis(std::ostream& os, std::string indent = "") : _os(os), _indent(indent) {}

        void operator()(std::map<std::string, ast::Value> const& map) const {
            _os << "map {\n";
            for (auto& entry : map) {
                _os << _indent << "    " << entry.first << '|';
                boost::apply_visitor(vis(_os, _indent+"    "), entry.second);
                _os << "\n";
            }
            _os << _indent << "}\n";
        }
        void operator()(std::string const& s) const {
            _os << s;
        }

      private:
        std::ostream& _os;
        std::string _indent;
    };
    boost::apply_visitor(vis(os), value);
    return os;
}

int main()
{
    std::string const Example1 = "Key1=Value1 ; Key2 = 01-Jan-2015; Key3 = 2.7181; Key4 = Johnny";
    std::string const Example2 = "Key1 = Value1; Key2 = {InnerK1 = one; IK2 = 11-Nov-2011;};";
    std::string const Example3 = "K1 = V1; K2 = {IK1=IV1; IK2=IV2;}; K3=V3; K4 = {JK1=JV1; JK2=JV2;};";

    std::cout << Parse2(Example1.begin(), Example1.end()) << "\n";
    std::cout << Parse2(Example2.begin(), Example2.end()) << "\n";
    std::cout << Parse2(Example3.begin(), Example3.end()) << "\n";
}
