#define BOOST_SPIRIT_DEBUG
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace client
{
    typedef std::map<std::string, std::string> key_value_map_t;

    struct mini_ini
    {
        std::string name;
        key_value_map_t key_values_map;
    };
} // client

BOOST_FUSION_ADAPT_STRUCT(
    client::mini_ini,
    (std::string, name)
    (client::key_value_map_t, key_values_map)
)

namespace client
{
    namespace qi      = boost::spirit::qi;
    namespace ascii   = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    template <typename Iterator>
    struct ini_grammar : qi::grammar<Iterator, mini_ini(), ascii::blank_type>
    {
        ini_grammar() : ini_grammar::base_type(section_, "section")
        {
            using qi::char_;
            using qi::on_error;
            using qi::fail;
            using namespace qi::labels;
            using phoenix::construct;
            using phoenix::val;

            key_ = +char_("a-zA-Z_0-9");
            pair_ = key_ >> '=' >> *char_;
            section_ = '[' >> key_ >> ']' >> '\n' >> *(pair_ >> '\n');

            BOOST_SPIRIT_DEBUG_NODES((key_)(pair_)(section_))

            on_error<fail>
            (
                section_
              , std::cout
                    << val("Error! Expecting ")
                    << _4                               // what failed?
                    << val(" here: \"")
                    << construct<std::string>(_3, _2)   // iterators to error-pos, end
                    << val("\"")
                    << std::endl
            );
        }

        qi::rule<Iterator, std::string(), ascii::blank_type> key_;
        qi::rule<Iterator, mini_ini(), ascii::blank_type> section_;
        qi::rule<Iterator, std::pair<std::string, std::string>(), ascii::blank_type> pair_;
    };
} // client

int
main()
{
    std::string storage =
        "[section]\n"
        "key1=val1\n"
        "key2=val2\n";
    client::mini_ini ini;
    typedef client::ini_grammar<std::string::const_iterator> ini_grammar;
    ini_grammar grammar;

    using boost::spirit::ascii::blank;
    std::string::const_iterator iter = storage.begin();
    std::string::const_iterator end = storage.end();
    bool ok = phrase_parse(iter, end, grammar, blank, ini);

    if (ok) {
        std::cout << "Parse success\n";
    } else {
        std::cout << "Parse failure\n";
    }

    if (iter != end) {
        std::cout << "Remaining unparsed: '" << std::string(iter, end) << "'\n";
    }

    return ok && (iter==end)? 0 : 1;
}
