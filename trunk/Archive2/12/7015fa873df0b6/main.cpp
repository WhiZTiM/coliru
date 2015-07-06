#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi_lit.hpp>

int main() {
    using namespace boost::spirit::qi;
    using boost::phoenix = phx;
    std::string strLinesRecur = "%%DocumentNeededResources: CMap (90pv-RKSJ-UCS2C)";
    std::string a, b, c;
    
    phrase_parse(begin(strLinesRecur), end(strLinesRecur),
        (char_('%') >> char_('%')
            >> +(char_ - ':') >> char_(':')) >> +(char_ - '(') >> char_('(')
            >> +char_[phx::ref(a) = _1] >> char_('('),
        ' '
    );
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
}