//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
namespace qi  = boost::spirit::qi;

struct CMyTag
{
    std::string tagName;
    std::string tagData;
};
BOOST_FUSION_ADAPT_STRUCT(::CMyTag, (std::string, tagName) (std::string, tagData));

template <typename Iterator, typename Skipper = qi::space_type>
struct testTag_grammar : qi::grammar<Iterator, std::vector<CMyTag>(), Skipper>
{
    testTag_grammar() :
        testTag_grammar::base_type(data)
    {
        using namespace qi;

        data = +( ('{' >> tag >> '}') | text );

        type.add
            ("img",   "img")
            ("var",   "var")
            ("inc",   "inc")
            ("blank", "blk")
            ("ref",   "ref");

        tag  = lexeme[type >> &char_(" {}")] >> lexeme[*~char_("{}")];
        text = attr("text")                  >> lexeme[+~char_("{}")];

        BOOST_SPIRIT_DEBUG_NODES( (data) (tag) (text))
    }

  private:
    qi::symbols<char, std::string> type;
    qi::rule<Iterator, CMyTag(), Skipper>              tag, text;
    qi::rule<Iterator, std::vector<CMyTag>(), Skipper> data;
};

int main() {
    testTag_grammar<std::string::const_iterator> l_gramar;
    std::string const l_test = "asd {img} {ref I}sdkflsdlk {img} wmrwerml";

    std::vector<CMyTag> l_result;
    auto f = l_test.begin(), l = l_test.end();
    bool result = qi::phrase_parse(f, l, l_gramar, qi::space, l_result);

    if (result) {
        std::cout << "Parse success: " << l_result.size() << "\n";

        for (auto& v : l_result)
            std::cout << "Name '" << v.tagName << "', Data '" << v.tagData << "'\n";
    }
    else {
        std::cout << "Parse failed\n";
    }

    if (f!=l) {
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
