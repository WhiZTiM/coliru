// following example from:
// http://www.boost.org/doc/libs/1_58_0/libs/spirit/example/qi/employee.cpp, and
// num_list4.cpp, and others

#define BOOST_SPIRIT_DEBUG 1
#define BOOST_SPIRIT_DEBUG_PRINT_SOME 200
#define BOOST_SPIRIT_DEBUG_OUT std::cerr

// std includes
#include <iostream>
#include <string>
// boost includes
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace frontend {
    namespace spirit = boost::spirit;
    namespace qi     = spirit::qi;
    namespace ascii  = spirit::ascii;

    struct cursor {
        std::string file;
        unsigned long long offset;
        unsigned long long line;
        unsigned long long col;
        // verify inputs using enum
        // decl/ref/defn/call
        std::string reference_type;
        // variable/function/scope/label/type
        std::string specifier;
        // if variable/function, then type
        std::string type;
        std::string language;
        std::string name;
        std::string scope;
    };
}

// adapt struct to boost fusion
BOOST_FUSION_ADAPT_STRUCT(frontend::cursor, (std::string, file),
                          (unsigned long long, offset),
                          (unsigned long long, line), (unsigned long long, col),
                          (std::string, reference_type),
                          (std::string, specifier), (std::string, type),
                          (std::string, language), (std::string, name),
                          (std::string, scope))

// NOTE: blank_type doesn't skip newlines
namespace frontend {

    template <typename Iterator>
    struct cursor_parser : public qi::grammar<Iterator, std::vector<cursor>(), qi::blank_type> {

        cursor_parser() : cursor_parser::base_type(vec) {
            using qi::uint_;
            using qi::eol;
            using qi::lexeme;
            using qi::char_;

            quoted_string %= lexeme['"' >> *(char_ - '"') >> '"'];

            start %=
                quoted_string  >> ','   >>  // file
                uint_          >> ','   >>  // offset
                uint_          >> ','   >>  // line
                uint_          >> ','   >>  // col
                quoted_string  >> ','   >>  // reference_type
                quoted_string  >> ','   >>  // specifier
                quoted_string  >> ','   >>  // type
                quoted_string  >> ','   >>  // language
                quoted_string  >> ','   >>  // name
                quoted_string; // scope

            vec %= start % eol;

            BOOST_SPIRIT_DEBUG_NODES((quoted_string)(start)(vec))
        }

        private:
        qi::rule<Iterator, std::string()        , qi::blank_type> quoted_string;
        qi::rule<Iterator, cursor()             , qi::blank_type> start;
        qi::rule<Iterator, std::vector<cursor>(), qi::blank_type> vec;
    };
}

int main() {
    // '"f",111,222,333,"ref_type","spc","type","lan","name","scop"'

    using It = boost::spirit::istream_iterator;

    noskipws(std::cin);
    It start_in(std::cin >> std::noskipws), end_in;
    std::vector<frontend::cursor> v;

    if (phrase_parse(start_in, end_in, frontend::cursor_parser<It>(), frontend::qi::blank, v)) {
        for (auto &c : v) {
            std::cout << boost::fusion::as_vector(c) << std::endl;
        }
        std::cerr << "success!" << std::endl;
    } else {
        std::cerr << "failure!" << std::endl;
        return 1;
    }
}
