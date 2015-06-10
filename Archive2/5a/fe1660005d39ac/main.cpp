#define BOOST_SPIRIT_USE_PHOENIX_V3 1
#define BOOST_SPIRIT_DEBUG 1

#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <iostream>
#include <string>

#include <boost/spirit/include/phoenix_stl.hpp>

#include <boost/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>

// this solution for lazy make shared comes from the SO forum, user sehe.
// https://stackoverflow.com/questions/21516201/how-to-create-boost-phoenix-make-shared
//    post found using google search terms `phoenix construct shared_ptr`
// changed from boost::shared_ptr to std::shared_ptr
namespace {
    template <typename T> struct make_shared_f {
        template <typename... A> struct result { typedef std::shared_ptr<T> type; };

        template <typename... A> typename result<A...>::type operator()(A &&... a) const {
            return std::make_shared<T>(std::forward<A>(a)...);
        }
    };

    template <typename T> using make_shared_ = boost::phoenix::function<make_shared_f<T> >;
}

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator, typename Skipper = ascii::space_type>
struct SystemParser : qi::grammar<Iterator, std::vector<std::shared_ptr<std::string> >(), Skipper> {

    SystemParser() : SystemParser::base_type(variable_group_) {
        namespace phx = boost::phoenix;
        using qi::_1;
        using qi::_val;
        using qi::eps;
        using qi::lit;

        var_counter = 0;

        declarative_symbols.add("variable_group", 0);

        variable_group_       = "variable_group" > genericvargp_ > ';';
        genericvargp_         = new_variable_ % ',';                                                                                      //
        new_variable_         = unencountered_symbol_ [_val = make_shared_<std::string>()(_1)];
        unencountered_symbol_ = valid_variable_name_ - (encountered_variables | declarative_symbols);
        valid_variable_name_  = +qi::alpha >> *(qi::alnum | qi::char_("[]_"));

        BOOST_SPIRIT_DEBUG_NODES((variable_group_) (valid_variable_name_) (unencountered_symbol_) (new_variable_) (genericvargp_))
    }

    // rule declarations.  these are member variables for the parser.
    qi::rule<Iterator, std::vector<std::shared_ptr<std::string> >(), Skipper> variable_group_;
    qi::rule<Iterator, std::vector<std::shared_ptr<std::string> >(), Skipper> genericvargp_;
    qi::rule<Iterator, std::shared_ptr<std::string>() > new_variable_;
    qi::rule<Iterator, std::string()> unencountered_symbol_;
    qi::rule<Iterator, std::string()> valid_variable_name_;

    unsigned var_counter;
    qi::symbols<char, qi::unused_type> encountered_variables;
    qi::symbols<char, qi::unused_type> declarative_symbols;
};

int main()
{
    std::vector<std::shared_ptr<std::string> > V;
    std::string str = "variable_group x, y, z; ";

    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();

    SystemParser<std::string::const_iterator> S;

    bool s = phrase_parse(iter, end, S, boost::spirit::ascii::space, V);

    if (s)
    {
        std::cout << "Parse succeeded: " << V.size() << " variables\n";
        for (auto& s : V)
            std::cout << " - '" << *s << "'\n";
    }
    else
        std::cout << "Parse failed\n";

    if (iter!=end)
        std::cout << "Remaining unparsed: '" << std::string(iter, end) << "'\n";
}
