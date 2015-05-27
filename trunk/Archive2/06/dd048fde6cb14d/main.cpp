#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <iomanip>

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct HTMLEscape_grammar : qi::grammar<Iterator, std::string()>
{
    HTMLEscape_grammar() :
        HTMLEscape_grammar::base_type(text)
    {
        htmlescapes.add("&nbsp;", { '\xEC', '\x8A', '\xAD' });
        htmlescapes.add("&shy;",  { '\xEC', '\x8A', '\xAD' });

        text = *(htmlescapes | qi::char_);
    }

private:
    qi::symbols<char, std::vector<char> > htmlescapes;
    qi::rule<Iterator, std::string()> text;
};

int main() {
    std::string const l_test = "test&shy;as test simple&shy;test";
    HTMLEscape_grammar<std::string::const_iterator> l_gramar;

    std::string l_ast;
    bool result = qi::parse(l_test.begin(), l_test.end(), l_gramar, l_ast);

    if (result) {
        std::cout << "Parse success\n";
        for (unsigned char ch : l_ast)
            std::cout << std::setw(2) << std::setfill('0') << std::hex << std::showbase << static_cast<int>(ch) << " ";
    } else
    {
        std::cout << "Parse failure\n";
    }
}
