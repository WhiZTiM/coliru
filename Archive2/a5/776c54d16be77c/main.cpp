#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <vector>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

namespace termcxx { namespace parser {

    namespace ascii = boost::spirit::ascii;
    namespace px    = boost::phoenix;

    //using qi::double_;
    using ascii::blank;
    //using px::ref;
    using px::construct;

    //using qi::eps;
    //using qi::lit;
    using qi::_val;
    using qi::_1;
    using ascii::char_;
    using ascii::graph;
    using qi::eol;
    using qi::eoi;

    struct context
    {
        int dummy;

        context () = default;
        context (context const &) = default;
        context (std::vector<char> a)
        { }
        context (std::vector<char> a, std::vector<char> b)
        { }
    };

} }


BOOST_FUSION_ADAPT_STRUCT(
    termcxx::parser::context,
    (int, dummy))

namespace termcxx { namespace parser {

    template <typename Iterator>
    struct parser : qi::grammar<Iterator, context()>
    {
        qi::rule<Iterator, std::string()> comment_line;
        qi::rule<Iterator, std::string()> empty_line;
        qi::rule<Iterator, std::string()> def_first_line;
        qi::rule<Iterator, std::string()> def_subsequent_line;
        qi::rule<Iterator, std::string()> definition;
        qi::rule<Iterator, context()> start;

        parser() : parser::base_type(start)
        { 
            empty_line          = *blank >> eol;
            comment_line        = *blank >> '#' >> *(char_ - eol) >> (eol|eoi);
            def_first_line      = graph >> +(char_ - eol)         >> (eol|eoi);
            def_subsequent_line = +blank >> +(char_ - eol)        >> (eol|eoi);

            definition          = (def_first_line >> *def_subsequent_line);

            start               = (  
                                    *(comment_line | empty_line | definition)
                                  ) [ _val = px::construct<context>() ]
                                  ;

            BOOST_SPIRIT_DEBUG_NODES((start)(def_first_line)(def_subsequent_line)(definition)(empty_line)(comment_line))
        }
    };

} }

int main()
{
    using It = boost::spirit::istream_iterator;
    termcxx::parser::parser<It> g;

    It f(std::cin >> std::noskipws), l;
    termcxx::parser::context data;
    if (qi::parse(f,l,g,data))
        std::cout << "Success\n";
    else
        std::cout << "Failure\n";

    if (f != l)
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}
