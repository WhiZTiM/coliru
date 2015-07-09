#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename It, typename Skipper = qi::space_type>
struct my_grammar : qi::grammar<It, std::string(), Skipper> {

    my_grammar() : my_grammar::base_type(start) {
        using namespace qi;

        start = dq_literal 
              | sq_literal;

        dq_literal = raw [ '"' >> *("\\\"" | ~char_('"')) >> '"' ]; 
        sq_literal = raw [ "'" >> *("\\'"  | ~char_("'")) >> "'" ]; 

        BOOST_SPIRIT_DEBUG_NODES(
                (start)(dq_literal)(sq_literal)
            )
    }

  private:
    qi::rule<It, std::string(), Skipper> start;

    // drop skipper to make these rules implicitly 'lexeme'
    // see: http://stackoverflow.com/questions/17072987/boost-spirit-skipper-issues/17073965#17073965
    qi::rule<It, std::string()> 
        dq_literal,
        sq_literal;
};

int main() {
    using It = std::string::const_iterator;
    my_grammar<It> g;

    for (std::string const& input : {
            "\"hello world\"",
            "\"hello \\\"world\\\"\"",
            "'bye world'",
            "'bye \"\\'world\\'\"'",
            "bogus" })
    {
        std::cout << "\n------- Parsing: " << input << '\n';
        It f = input.begin(), l = input.end();

        std::string result;
        bool ok = qi::phrase_parse(f, l, g, qi::space, result);

        if (ok)
            std::cout << "Parse success: " << result << "\n";
        else
            std::cout << "Parse failed\n";

        if (f!=l)
            std::cout << "Remaining unparsed input '"  << std::string(f,l) << "'\n";
    }
}
