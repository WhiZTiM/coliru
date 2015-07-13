#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace px    = boost::phoenix;
namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

using ValueType = boost::variant<int, unsigned, double>;
using ResultType = std::vector<std::vector<ValueType>>;

enum class CSVDataType { Int, UInt, Double };

namespace boost { namespace spirit { namespace qi { // FOR DEBUG
    template <typename... T> std::ostream& operator<<(std::ostream& os, rule<T...> const*)                     { return os << "(lazy rule)";       }
    template <typename... T> std::ostream& operator<<(std::ostream& os, std::vector<rule<T...> const*> const&) { return os << "(column mappings)"; }
} } }

template<typename Iterator, typename Skipper = ascii::blank_type>
struct TypedCSVGrammar: qi::grammar<Iterator, ResultType(), Skipper> {

    TypedCSVGrammar() : TypedCSVGrammar::base_type(start, "csv")
    {
        using namespace qi::labels;

        header = *types;

        csv    = qi::omit[ header [ _cols = _1 ] ] > qi::eol
               > qi::repeat(_current=0, px::size(_cols)) [ qi::lazy(*_cols[_current++]) ] % qi::eol
               > *qi::eol
               ;

        start = csv;

        BOOST_SPIRIT_DEBUG_NODES((start)(csv)(header));

        qi::on_error<qi::fail> (csv, px::ref(std::cout)
                    << "Error! Expecting " << _4                                  // what failed?
                    << " here: \""         << px::construct<std::string>(_3, _2)  // iterators to error-pos, end
                    << "\"\n"
            );
    }

  private:
    using cell_parser_t = qi::rule<Iterator, ValueType(), Skipper>;
    using dynamic       = cell_parser_t const*;

    struct types_: qi::symbols<char, dynamic> {
        cell_parser_t
            int_cell    = qi::int_,
            uint_cell   = qi::uint_,
            double_cell = qi::double_;

        types_() {
            this->add
                ("int",      &int_cell)
                ("unsigned", &uint_cell)
                ("double",   &double_cell);
            BOOST_SPIRIT_DEBUG_NODES((int_cell)(uint_cell)(double_cell))
        }
    } types;

    using state = qi::locals<std::vector<dynamic>, size_t>;
    qi::_a_type _cols;
    qi::_b_type _current;

    qi::rule<Iterator, ResultType(),             Skipper> start;
    qi::rule<Iterator, std::vector<dynamic>(),   Skipper> header;
    qi::rule<Iterator, ResultType(),             Skipper, state>  csv;
};

int main() {
    using It = boost::spirit::istream_iterator;

    It f(std::cin >> std::noskipws), l;
    TypedCSVGrammar<It> g;
    ResultType data;
    bool ok = qi::phrase_parse(f, l, g, ascii::blank, data);
    if (ok) {
        std::cout << "Parse success\n";

        for(auto& row: data) {
            for(auto& cell: row) std::cout << cell << "\t";
            std::cout << "\n";
        }
    }
    else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
