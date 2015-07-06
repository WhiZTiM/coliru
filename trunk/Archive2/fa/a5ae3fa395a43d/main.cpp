#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi_lit.hpp>

int main() {
    using namespace boost::spirit::qi;
    namespace phx = boost::phoenix;
    std::string strLinesRecur = "%%DocumentNeededResources: CMap (90pv-RKSJ-UCS2C)";
    std::string res;
    
    using boost::spirit::ascii::alpha;
    using boost::spirit::ascii::alnum;
    using boost::spirit::ascii::blank;
    auto code = copy(+(alnum | char_('-')));
    auto grammar = copy(
        (char_('%') >> char_('%') >> +alpha >> char_(':')) 
            >> +alpha >> char_('(') >> as_string[lexeme[code]][phx::ref(res) = _1] >> char_(')'));
    phrase_parse(begin(strLinesRecur), end(strLinesRecur), grammar, blank);
    std::cout << "Result: " << res << std::endl;
}